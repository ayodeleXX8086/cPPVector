
#include <cassert>
#include <iostream>
#include <memory>
#include <utility>

#include "../core_implementation/Vectors.h"

static int g_run = 0, g_pass = 0;
static void run(const char* name, void (*fn)()) {
    std::cout << "[ RUN  ] " << name << '\n';
    ++g_run;
    fn();
    ++g_pass;
    std::cout << "[  OK  ] " << name << '\n';
}

struct TestClass {
    static int destructor_count;
    int a;
    std::size_t n;
    std::size_t _size;
    std::string b;
    std::string* arr;
    TestClass(): a(0), n(0), _size(0), arr(nullptr) {}
    TestClass(const int id, std::string name, const std::size_t count): a(id), n(count), _size(0), b(std::move(name)), arr(new std::string[count]) {}
    TestClass(const TestClass& other): a(other.a), n(other.n), _size(other._size), b(other.b) {
        if (n>0) {
            std::unique_ptr<std::string[]>temp(new std::string[n]{other.b});
            std::ranges::copy(other.arr, other.arr+n, temp.get());
            arr = temp.release();
        }
    }
    TestClass(TestClass&& other) noexcept : a(other.a), n(other.n), _size(other._size), b(core_implementation::move(other.b)), arr(other.arr) {
        other.a = 0;
        other.arr = nullptr;
        other.n = 0;
    }
    void add_string(std::string&& str)  {
        *(arr+(_size++%n))=std::move(str);
    }

    std::string* begin() const {
        return arr;
    }

    std::string* end() const {
        return arr+_size;
    }
    TestClass& operator=(TestClass&& other) noexcept {
        if (this != &other) {
            delete [] arr;
            arr = other.arr;
            a=other.a;
            b = core_implementation::move(other.b);
            n=other.n;
            other.a=0;
            other.arr=nullptr;
            other.n=0;
        }
        return *this;
    }
    TestClass& operator=(const TestClass& other) noexcept{
        if (this != &other) {
            std::unique_ptr<std::string[]>temp;
            if (other.n>0) {
                temp = std::make_unique<std::string[]>(other.n);
                std::ranges::copy(other.arr, other.arr+other.n, temp.get());
            }
            a = other.a;
            b = other.b;
            delete [] arr;
            arr = temp.release();
            n=other.n;
        }
        return *this;
    }
    ~TestClass() {
        ++destructor_count;
        delete[] arr;
    }
};
int TestClass::destructor_count = 0;

static void test_default_initialization() {
    core_implementation::Vectors<int> vec;
    assert(vec.size() == 0);
    vec.push_back(2);
    assert(vec.capacity() == 1);
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    assert(vec.size() == 4);
    assert(vec.capacity() > 1);
}

static void test_indexing_vector() {
    core_implementation::Vectors<int> vec(2);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    assert(vec[0]==0);
    assert(vec[1]==0);
    assert(vec[2]==2);
    assert(vec[3]==3);
    assert(vec[4]==4);
}

static void test_move_operation() {
    core_implementation::Vectors<int> vec;
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    core_implementation::Vectors<int> vec2=std::move(vec);
    assert(vec2[0]==2);
    assert(vec2[1]==3);
    assert(vec2[2]==4);
    assert(vec.size()==0);
}

static void test_initialization_list() {
    core_implementation::Vectors<int> vec=std::move(core_implementation::Vectors<int>({4,5,6,7}));
    assert(vec.size()==4);
    assert(vec[0]==4);
    assert(vec[1]==5);
    assert(vec[2]==6);
    assert(vec[3]==7);
    vec.push_back(2);
    assert(vec.size()==5);
}

static void test_destroyed_method_on_pop_back() {
        core_implementation::Vectors<TestClass> vec;
        TestClass test(1, "Test1", 20);
        test.add_string("Testing1");
        test.add_string("Testing2");
        vec.push_back(std::move(test));
        assert(vec.size()==1);
        assert(TestClass::destructor_count==0);
        const auto first=vec.begin();
        std::cout<<"Name " << first->b << "\n";
        assert(first->b=="Test1");
        assert(first->n==20);
        assert(first->a==1);
        vec.pop_back();
        assert(vec.size()==0);
        assert(test.a==0);
        assert(TestClass::destructor_count==1);
}

int main() {
    run("test_default_initialization", test_default_initialization);
    run("test_indexing_vector", test_indexing_vector);
    run("test_move_operation", test_move_operation);
    run("test_initialization_list", test_initialization_list);
    run("test_destroyed_method_on_pop_back", test_destroyed_method_on_pop_back);
}