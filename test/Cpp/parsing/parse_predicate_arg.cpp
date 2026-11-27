// clang-format off
// Regression-test for issue #28. This should fail during the parsing-stage.
// Small example where the parser for predicates is too permissive. 
// The contract is syntactically incorrect (typo in requires) which caused the 
// old parser to interpret lines 10-22 as the definition of a predicate argument

/*@
declare using namespace pallasSpec;
@*/

/*@
abstract predicate myPred(int a, int b);
@*/


/*@
require _sep(_Perm(a, _writePerm), 
             _Perm(b, _writePerm));
require myPred(a, b);
ensures _sep(_Perm(a, _writePerm), 
             _Perm(b, _writePerm));
ensures  myPred(a, b);
ensures *a == _old(*b) && *b == _old(*a);
@*/
void foo(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// RUN: %not %Spec2IR %s -lib %CppSpecLib -m -lang Cpp 2>&1 | %FileCheck %s
// CHECK: Unable to parse the source file.