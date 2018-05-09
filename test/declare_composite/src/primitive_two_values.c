/* This is a managed file. Do not delete this comment. */

#include <include/test.h>

void test_primitive_two_values_tc_bitmask(
    test_primitive_two_values this)
{

}

void test_primitive_two_values_tc_bool(
    test_primitive_two_values this)
{
    const char *input = "test/s_bool obj: false, true";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_bool *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_bool_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assert(obj->m == false);
    test_assert(obj->n == true);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_char(
    test_primitive_two_values this)
{
    const char *input = "test/s_char obj: 'a', 'b'";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_char *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_char_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assert(obj->m == 'a');
    test_assert(obj->n == 'b');

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_enum(
    test_primitive_two_values this)
{
    const char *input = "test/s_enum obj: Black, Red";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_enum *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_enum_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assert(obj->m == Test_Black);
    test_assert(obj->n == Test_Red);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_float32(
    test_primitive_two_values this)
{
    const char *input = "test/s_float32 obj: 10.5, 20.5";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_float32 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_float32_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertflt(obj->m, 10.5);
    test_assertflt(obj->n, 20.5);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_float64(
    test_primitive_two_values this)
{
    const char *input = "test/s_float64 obj: 10.5, 20.5";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_float64 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_float64_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertflt(obj->m, 10.5);
    test_assertflt(obj->n, 20.5);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_int16(
    test_primitive_two_values this)
{
    const char *input = "test/s_int16 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_int16 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_int16_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_int32(
    test_primitive_two_values this)
{
    const char *input = "test/s_int32 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_int32 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_int32_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_int64(
    test_primitive_two_values this)
{
    const char *input = "test/s_int64 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_int64 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_int64_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_int8(
    test_primitive_two_values this)
{
    const char *input = "test/s_int8 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_int8 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_int8_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_octet(
    test_primitive_two_values this)
{
    const char *input = "test/s_octet obj: 0x10, 0x20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_octet *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_octet_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 0x10);
    test_assertint(obj->n, 0x20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_string(
    test_primitive_two_values this)
{
    const char *input = "test/s_string obj: 'Hello World', 'Foo Bar'";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_string *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_string_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertstr(obj->m, "Hello World");
    test_assertstr(obj->n, "Foo Bar");

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_uint16(
    test_primitive_two_values this)
{
    const char *input = "test/s_uint16 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_uint16 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_uint16_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_uint32(
    test_primitive_two_values this)
{
    const char *input = "test/s_uint32 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_uint32 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_uint32_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_uint64(
    test_primitive_two_values this)
{
    const char *input = "test/s_uint64 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_uint64 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_uint64_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_uint8(
    test_primitive_two_values this)
{
    const char *input = "test/s_uint8 obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_uint8 *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_uint8_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}


void test_primitive_two_values_tc_word(
    test_primitive_two_values this)
{
    const char *input = "test/s_word obj: 10, 20";
    ast_Node ast = cortoscript_ast_parse(input);
    test_assert(ast != NULL);
    test_assert(corto_typeof(ast) == (corto_type)ast_Scope_o);
    test_assertint(corto_ll_count(ast_Scope(ast)->statements), 1);

    int16_t ret = cortoscript_ast_declare(data_o, ast);
    test_assert(ret == 0);

    test_s_word *obj = corto_lookup(data_o, "obj");
    test_assert(obj != NULL);
    test_assert(corto_typeof(obj) == (corto_type)test_s_word_o);
    test_assert(corto_check_state(obj, CORTO_VALID));
    test_assert(corto_countof(obj) == 2);
    test_assertint(obj->m, 10);
    test_assertint(obj->n, 20);

    test_assert(corto_delete(ast) == 0);
    test_assert(corto_release(obj) == 1);
    test_assert(corto_delete(obj) == 0);
}
