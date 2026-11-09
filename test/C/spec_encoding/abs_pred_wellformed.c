// Test that abstract predicates are encoded correctly and can be called.
// RUN: %Spec2IR %s -lib %CSpecLib -m | %FileCheck %s

/*@
abstract predicate absCPred(bool b1, bool b2);
@*/

/*@
requires absCPred(1, 0);
@*/
int foo (int v1, int v2) {
    return 42;
}


// COM: Predicate is called in Wrapper-Function
// CHECK-LABEL: define {{.+}} i1 @PALLAS_SPEC_0(
// CHECK-SAME: !pallas.exprWrapper {{![0-9]+}}
// CHECK: [[res:%[0-9]+]] = call {{.+}} i1 @absCPred(i1 {{.+}} true, i1 {{.+}} false)
// CHECK: ret i1 [[res]]

// COM: Predicate-definition is present, labeled and merked as an abstract predicate
// CHECK-LABEL: define {{.*}} i1 @absCPred(
// CHECK-SAME: i1 {{.*}} %0, i1 {{.*}} %1)
// CHECK-SAME: !pallas.predDef [[pDefMarker:![0-9]+]]
// CHECK: [[pDefMarker]] = !{i1 false, i1 true}