// Test that abstract predicates are encoded correctly.
// RUN: %Spec2IR %s -lib %CppSpecLib -m --lang=Cpp | %FileCheck %s
// RUN: %Spec2IR %s -lib %CppSpecLib -m --lang=Cpp | %FileCheck %s --check-prefix=CHECK2

/*@
abstract predicate myAbstractPredicate(int *loc, int val);
@*/

/*@
requires myAbstractPredicate(ptr, 42);
@*/
int bar (int *ptr) {
    return 42;
}


// COM: Predicate is called in Wrapper-Function
// CHECK-LABEL: define {{.+}} i1 @_Z13PALLAS_SPEC_0Pi(
// CHECK-SAME: !pallas.exprWrapper {{![0-9]+}}
// CHECK: [[res:%[0-9]+]] = call {{.+}} i1 @_Z19myAbstractPredicatePii(ptr {{.+}} %0, i32 {{.+}} 42)
// CHECK: ret i1 [[res]]

// COM: Predicate-definition is encoded correctly
// CHECK2-LABEL: define {{.*}} i1 @_Z19myAbstractPredicatePii(
// CHECK2-SAME: ptr {{.*}} %0, i32 {{.*}} %1)
// CHECK2-SAME: !pallas.predDef [[pDefMarker:![0-9]+]]
// CHECK2: [[pDefMarker]] = !{i1 false, i1 true}