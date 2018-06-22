/* This is a managed file. Do not delete this comment. */

#include <corto/script/declare/declare.h>

int16_t declare_Visitor_construct(
    declare_Visitor this)
{
    if (this->from) {
        corto_set_ref(&this->current_scope, this->from);
    } else {
        corto_set_ref(&this->current_scope, root_o);
    }

    if (!this->typesystem) {
        corto_set_ref(&this->typesystem, corto_lang_o);
    }

    return corto_super_construct(this);
}

int16_t declare_Visitor_prepareInitializer(
    declare_Visitor this,
    ast_Initializer initializer,
    corto_type type)
{
    /* First propagate types to all expressions in initializer */
    corto_try (ast_Initializer_propagateType(initializer, type), NULL);

    /* Now visit expressions to resolve identifiers */
    corto_try (ast_Visitor_visit(this, initializer), NULL);

    /* Now fold expressions */
    corto_try (!ast_Initializer_fold(initializer), NULL);

    return 0;
error:
    return -1;
}

static
char* declare_visitor_arglist_to_string(
    ast_FunctionArgumentList args)
{
    corto_buffer buff = CORTO_BUFFER_INIT;

    corto_buffer_appendstr(&buff, "(");
    uint32_t count = 0;

    corto_iter it = corto_ll_iter(args);
    while (corto_iter_hasNext(&it)) {
        ast_FunctionArgument arg = corto_iter_next(&it);

        if (count) {
            corto_buffer_appendstr(&buff, ",");
        }

        if (arg->inout == CORTO_OUT) {
            corto_buffer_appendstr(&buff, "out:");
        } else if (arg->inout == CORTO_INOUT) {
            corto_buffer_appendstr(&buff, "inout:");
        }

        corto_type type = ast_Storage_get_object(arg->type);
        if (!type) {
            corto_throw(
                "missing type for argument '%s' in function declaration",
                arg->name);
            goto error;
        }

        corto_buffer_appendstr(&buff, corto_fullpath(NULL, type));

        if (arg->is_reference) {
            corto_buffer_appendstr(&buff, "&");
        }

        corto_buffer_appendstr(&buff, " ");

        corto_buffer_appendstr(&buff, arg->name);

        count ++;
    }

    corto_buffer_appendstr(&buff, ")");

    return corto_buffer_str(&buff);
error:
    return NULL;
}

int16_t declare_Visitor_visitDeclaration(
    declare_Visitor this,
    corto_script_ast_Declaration node)
{
    corto_object scope = this->current_scope;
    corto_type type = NULL;
    char *arg_list = NULL;

    if (node->type) {
        corto_try (ast_Visitor_visit(this, node->type), NULL);
        type = ast_Storage_get_object(node->type);
        corto_set_ref(&this->default_type, type);
    } else
    if (this->default_type) {
        if (!node->id->arguments ||
            corto_instanceof(corto_procedure_o, this->default_type))
        {
            type = this->default_type;
        }
    }

    if (!type) {
        /* Check if declaration is procedure */
        if (node->id->arguments) {
            type = corto_typeof(scope)->options.defaultProcedureType;
            if (!type) {
                /* If no default procedure type is available, use 'function' as
                 * default type */
                type = (corto_type)corto_function_o;
            }
        } else {
            type = corto_typeof(scope)->options.defaultType;
        }
    }

    /* If this is a statement that sets the scope and no type is provided or can
     * be derived (which is typical, since such statements usually appear at the
     * start of a script) assume 'package' as default type. */
    if (!type && node->set_scope) {
        type = (corto_type)corto_package_o;
    }

    if (!type) {
        corto_throw("cannot derive type for declaration in scope '%s'",
            corto_fullpath(NULL, scope));
        goto error;
    }

    if (!corto_instanceof(corto_type_o, type)) {
        corto_throw("object '%s' is not a type",
            corto_fullpath(NULL, type));
        goto error;
    }

    if (node->id->arguments) {
        corto_try (
          ast_Visitor_visitFunctionArguments(this, node->id->arguments), NULL);

        arg_list = declare_visitor_arglist_to_string(node->id->arguments);
        if (!arg_list) {
            corto_throw(NULL);
            goto error;
        }
    }

    /* If declaration has an initializer, set type of initializer to the type
     * of the declaration. This will allow the visitor to do precompute the
     * types for the value nodes in the initializer, which is required for doing
     * lookups for enumeration constants in the scope of the enumeration type */
    if (node->initializer) {
        corto_try(
            declare_Visitor_prepareInitializer(
                this, node->initializer, type), NULL);
    }

    corto_iter it = corto_ll_iter(node->id->ids);
    while (corto_iter_hasNext(&it)) {
        ast_Storage storage = corto_iter_next(&it);
        ast_Initializer object_initializer = NULL;
        const char *id = NULL;
        bool should_define = false;

        /* Regular identifier */
        if (corto_instanceof(ast_Identifier_o, storage)) {
            id = ast_Identifier(storage)->id;

        /* Initializer with object-specific initializer */
        } else if (corto_instanceof(ast_StorageInitializer_o, storage)) {
            ast_Storage id_expr = ast_StorageInitializer(storage)->expr;

            if (!corto_instanceof(ast_Identifier_o, id_expr)) {
                corto_throw("invalid identifier in declaration (%s)",
                    corto_idof(corto_typeof(id_expr)));
                goto error;
            }

            id = ast_Identifier(id_expr)->id;
            object_initializer = ast_StorageInitializer(storage)->initializer;

        /* Invalid storage for declaration identifier */
        } else {
            corto_throw("invalid identifier in declaration (%s)",
                corto_idof(corto_typeof(storage)));
            goto error;
        }

        /* Declare object */
        if (arg_list) {
            id = corto_asprintf("%s%s", id, arg_list);
        }

        corto_object from = scope;
        if (node->set_scope) {
            /* Identifiers in a scope-setting declaration are always resolved
             * relative to the parser scope */
            scope = this->from;
        }

        corto_object object;
        if (node->type) {
            /* If type is explicitly provided, use standard corto_declare, which
             * enforces that the returned object is of the specified type. */
            object = corto_declare(from, id, type);
        } else {
            /* If the type is implicit, make sure that the parser doesn't fail
             * when the object already exists with a different type. This call
             * provides functionality equivalent to corto_declare, minus the
             * type check. */
            object = corto(CORTO_RECURSIVE_DECLARE, {
                .parent = from,
                .id = id,
                .type = type
            });
        }
        if (!object) {
            corto_throw(
                "failed to declare object '%s' of type '%s' in scope '%s'",
                id,
                corto_fullpath(NULL, type),
                corto_fullpath(NULL, scope));
            goto error;
        }

        if (node->set_scope) {
            corto_set_ref(&this->current_scope, object);
        }

        if (arg_list) {
            /* Value is only freed when non-const value is assigned */
            free((char*)id);
        }

        ast_Storage_set_object(storage, object);

        corto_rw rw = corto_rw_init(type, object);

        /* If initializer is collection or composite, do initial push */
        if (type->kind == CORTO_COMPOSITE || type->kind == CORTO_COLLECTION) {
            corto_try(corto_rw_push(&rw, FALSE), NULL);
        }

        if (object_initializer || node->initializer) {
            should_define = true;

            /* If declaration has initializer, apply */
            if (node->initializer) {
                corto_try (
                    ast_Initializer_apply(
                      node->initializer, (uintptr_t)&rw), NULL);
            }

            /* If storage is identifier + initializer, apply initializer to new
             * object after global declaration initializer is applied */
            if (object_initializer) {
                corto_try(
                    declare_Visitor_prepareInitializer(
                        this, object_initializer, type), NULL);

                if (ast_Initializer_apply(object_initializer, (uintptr_t)&rw)) {
                    goto error;
                }
            }
        }

        /* If initializer has scope, visit scope before defining object */
        if (node->scope) {
            should_define = true;
            corto_object current_scope = this->current_scope;
            corto_type current_default_type = this->default_type;
            corto_set_ref(&this->current_scope, object);
            corto_set_ref(&this->default_type, NULL);
            corto_try (ast_Visitor_visit(this, node->scope), NULL);
            corto_set_ref(&this->current_scope, current_scope);
            corto_set_ref(&this->default_type, current_default_type);
        }

        /* Define object */
        if (should_define) {
            corto_try (corto_define(object), NULL);
        }

        corto_rw_deinit(&rw);
    }

    free (arg_list);
    return 0;
error:
    free (arg_list);
    return -1;
}

int16_t declare_Visitor_visitScope(
    declare_Visitor this,
    corto_script_ast_Scope node)
{
    corto_type prev_default_type = this->default_type;

    if (node->default_type) {
        corto_try (ast_Visitor_visit(this, node->default_type), NULL);

        corto_type type = ast_Storage_get_object(node->default_type);
        if (!type) {
            corto_throw(NULL);
            goto error;
        }

        corto_set_ref(&this->default_type, type);
    }

    if (ast_Visitor_visitScope_v(this, node)) {
        goto error;
    }

    corto_set_ref(&this->default_type, prev_default_type);

    return 0;
error:
    return -1;
}

int16_t declare_Visitor_visitStatement(
    declare_Visitor this,
    corto_script_ast_Statement node)
{
    return 0;
}

int16_t declare_Visitor_visitExpression(
    declare_Visitor this,
    corto_script_ast_Expression node)
{
    return 0;
}

int16_t declare_Visitor_visitStorage(
    declare_Visitor this,
    corto_script_ast_Storage node)
{
    corto_object typesystem = this->typesystem;
    corto_object scope = this->current_scope;
    corto_object obj;

    if (corto_instanceof(ast_Identifier_o, node)) {

        /* Named object */
        obj = declare_object_from_storage(
            typesystem, scope, this->search_scopes, node);
        if (!obj) {
            goto error;
        }

        ast_Storage_set_object(node, obj);
    } else
    if (corto_instanceof(ast_StorageInitializer_o, node)) {
        /* Anonymous object */
        ast_StorageInitializer anonymous_storage =
            ast_StorageInitializer(node);

        corto_object scope = this->current_scope;

        corto_type type =
            declare_object_from_storage(
                typesystem, scope, this->search_scopes, anonymous_storage->expr);
        if (!type) {
            corto_throw("failed to resolve type of anonymous object");
            goto error;
        }

        /* Create object with type */
        obj = corto_declare(NULL, NULL, type);

        ast_Storage_set_object(node, obj);

        /* Create initializer helper */
        corto_rw rw = corto_rw_init(type, obj);

        /* If initializer is collection or composite, do initial push */
        if (type->kind == CORTO_COMPOSITE || type->kind == CORTO_COLLECTION) {
            corto_try(corto_rw_push(&rw, FALSE), NULL);
        }

        /* Fold expressions in initializer */
        corto_try (declare_Visitor_prepareInitializer(
            this, anonymous_storage->initializer, type), NULL);

        /* Apply initializer to object */
        corto_try (
            ast_Initializer_apply(
                anonymous_storage->initializer, (uintptr_t)&rw), NULL);

        /* Define object */
        corto_try( corto_define(obj), NULL);

        /* Cleanup */
        corto_rw_deinit(&rw);
    }

    return 0;
error:
    return -1;
}

int16_t declare_Visitor_visitUse(
    declare_Visitor this,
    corto_script_ast_Use node)
{
    corto_object scope = corto_lookup(this->from, node->package);
    if (!scope) {
        corto_throw("could not find '%s' in use statement", node->package);
        goto error;
    }

    if (node->as_typesystem) {
        corto_set_ref(this->typesystem, scope);
    } else {
        declare_search_element el = {
            .scope = scope,
            .alias = node->alias
        };
        declare_search_elementList__append(this->search_scopes, &el);
    }

    return 0;
error:
    return -1;
}
