#include <cassert>
#include <iostream>
#include <utility>
#include "../IntVectors.h"

static int g_run = 0, g_pass = 0;
static void run(const char* name, void (*fn)()) {
    std::cout << "[ RUN  ] " << name << '\n';
    ++g_run;
    fn();
    ++g_pass;
    std::cout << "[  OK  ] " << name << '\n';
}

static void test_default_ctor_state() {
    IntVectors v;
    assert(v.size() == 0);
    assert(v.capacity() == 1);        // your fix: default seeds capacity=1
}

static void test_init_list_ctor() {
    IntVectors v = {1, 2, 3, 4};
    assert(v.size() == 4);
    assert(v.capacity() == 4);
    assert(v[0] == 1 && v[3] == 4);
}

static void test_push_back_after_default_grows() {
    IntVectors v = {1, 2};
    assert(v.size() == 2);
    assert(v.capacity() == 2);
    v.push_back(3);
    assert(v.size() == 3);
    assert(v[0]==1 && v[1] == 2 && v[2] == 3);
}

static void test_copy_ctor_independence() {
    IntVectors v = {1, 2};
    IntVectors v2(v);
    assert(v.size() == 2 && v2.size()==2);
    v2[0]=8;
    assert(v2[0]==8 && v[0]==1);
}

static void test_copy_assign_independence() {
    IntVectors v = {1, 2};
    IntVectors v2;
    v2 = v;
    assert(v.size() == 2 && v2.size()==2);
    v2[0]=8;
    assert(v2[0]==8 && v[0]==1);
}

static void test_self_copy_assign_safe() {
    IntVectors a = {1, 2, 3};
    a = a;                            // your self-assign guard should fire
    assert(a.size() == 3 && a[0] == 1 && a[2] == 3);
}

static void test_move_ctor_empties_source() {
    IntVectors v = {1, 2};
    assert(v.size() == 2);
    IntVectors v2(std::move(v));
    assert(v.size() == 0);
    assert(v.capacity() == 0);
    assert(v2.size() == 2);
    assert(v2[0] == 1 && v2[1] == 2);
    assert(v2.capacity() == 2);
}

static void test_move_assign_empties_source() {
    IntVectors v = {1, 2};
    IntVectors b = {91};
    assert(v.size() == 2);
    assert(v.capacity() == 2);
    b=std::move(v);
    assert(v.size() == 0 && v.capacity() == 0);
    assert(b.size() == 2);
    assert(b[0]==1 && b[1] == 2);
}

static void test_operator_bracket_throws_on_oob() {
    IntVectors v = {1, 2};
    bool caught = false;
    try {
        (void)v[5];
    }catch(std::exception& e) {
        caught = true;
    }
    assert(caught);
}

int main() {
    run("default_ctor_state",             test_default_ctor_state);
    run("init_list_ctor",                 test_init_list_ctor);
    run("push_back_after_default_grows",  test_push_back_after_default_grows);
    run("copy_ctor_independence",         test_copy_ctor_independence);
    run("copy_assign_independence",       test_copy_assign_independence);
    run("self_copy_assign_safe",          test_self_copy_assign_safe);
    run("move_ctor_empties_source",       test_move_ctor_empties_source);
    run("move_assign_empties_source",     test_move_assign_empties_source);
    run("operator_bracket_throws_on_oob", test_operator_bracket_throws_on_oob);
    std::cout << g_pass << "/" << g_run << " passed\n";
    return 0;
}
