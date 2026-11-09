// Test that abstract predicates are encoded correctly.
// RUN: %Spec2IR %s -lib %SwiftSpecLib -m --lang=Swift | %FileCheck %s

/*@
abstract predicate abstractSwiftPredicate(_ v1: Int64, _ v2: Int64);
@*/

/*@
predicate concreteSwiftPredicate(_ b1: Bool, _ b2: Bool) :=
    b1 == b2;
@*/

/*@
requires abstractSwiftPredicate(a, a + 1);
requires concreteSwiftPredicate(b, c);
@*/
func sFunc (a: Int64, b: Bool, c: Bool) -> Bool {
    return b && c;
}

// COM: Predicates are correctly encoded
// CHECK-DAG: define hidden swiftcc i1 [[absPred:@"\$.*22abstractSwiftPredicateySbs5Int64V_ADtF"]](i64 %0, i64 %1) {{.*}} !pallas.predDef [[absPredMD:![0-9]+]] {
// CHECK-DAG: define hidden swiftcc i1 [[concrPred:@"\$.*22concreteSwiftPredicateyS2b_SbtF"]](i1 %0, i1 %1) {{.*}} !pallas.predDef [[concrPredMD:![0-9]+]] {
// CHECK-DAG: [[absPredMD]] = !{i1 false, i1 true}
// CHECK-DAG: [[concrPredMD]] = !{i1 false, i1 false}

// COM: Both predicates are called
// CHECK-DAG: {{%[0-9]+}} = call swiftcc i1 [[absPred]](i64 {{%[0-9]+}}, i64 {{%[0-9]+}})
// CHECK-DAG: {{%[0-9]+}} = call swiftcc i1 [[concrPred]](i1 {{%[0-9]+}}, i1 {{%[0-9]+}})