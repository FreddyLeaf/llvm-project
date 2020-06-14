// NOTE: Assertions have been autogenerated by utils/update_test_checks.py
// RUN: %clang_cc1 -emit-llvm %s -std=c++2a -o %t.ll
// RUN: FileCheck -check-prefix=EVAL -input-file=%t.ll %s
// RUN: FileCheck -check-prefix=EVAL-FN -input-file=%t.ll %s
// RUN: FileCheck -check-prefix=EVAL-STATIC -input-file=%t.ll %s
// RUN: %clang_cc1 -emit-llvm %s -Dconsteval="" -std=c++2a -o %t.ll
// RUN: FileCheck -check-prefix=EXPR -input-file=%t.ll %s

// there is two version of symbol checks to ensure
// that the symbol we are looking for are correct
// EVAL-NOT: @__cxx_global_var_init()
// EXPR: @__cxx_global_var_init()

// EVAL-NOT: @_Z4ret7v()
// EXPR: @_Z4ret7v()
consteval int ret7() {
  return 7;
}

int test_ret7() {
  // EVAL-FN-LABEL: @_Z9test_ret7v(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[I:%.*]] = alloca i32, align 4
  // EVAL-FN-NEXT:    store i32 7, i32* [[I]], align 4
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = load i32, i32* [[I]], align 4
  // EVAL-FN-NEXT:    ret i32 [[TMP0]]
  //
  int i = ret7();
  return i;
}

// EVAL-STATIC: @global_i = global i32 7, align 4
int global_i = ret7();

// EVAL-STATIC: @_ZL7i_const = internal constant i32 5, align 4
constexpr int i_const = 5;

// EVAL-NOT: @_Z4retIv()
// EXPR: @_Z4retIv()
consteval const int &retI() {
  return i_const;
}

const int &test_retRefI() {
  // EVAL-FN-LABEL: @_Z12test_retRefIv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    ret i32* @_ZL7i_const
  //
  return retI();
}

int test_retI() {
  // EVAL-FN-LABEL: @_Z9test_retIv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = load i32, i32* @_ZL7i_const, align 4
  // EVAL-FN-NEXT:    ret i32 [[TMP0]]
  //
  return retI();
}

// EVAL-NOT: @_Z4retIv()
// EXPR: @_Z4retIv()
consteval const int *retIPtr() {
  return &i_const;
}

int test_retIPtr() {
  // EVAL-FN-LABEL: @_Z12test_retIPtrv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = load i32, i32* @_ZL7i_const, align 4
  // EVAL-FN-NEXT:    ret i32 [[TMP0]]
  //
  return *retIPtr();
}

const int *test_retPIPtr() {
  // EVAL-FN-LABEL: @_Z13test_retPIPtrv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    ret i32* @_ZL7i_const
  //
  return retIPtr();
}

// EVAL-NOT: @_Z4retIv()
// EXPR: @_Z4retIv()
consteval const int &&retIRRef() {
  return static_cast<const int &&>(i_const);
}

const int &&test_retIRRef() {
  return static_cast<const int &&>(retIRRef());
}

int test_retIRRefI() {
  // EVAL-FN-LABEL: @_Z14test_retIRRefIv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = load i32, i32* @_ZL7i_const, align 4
  // EVAL-FN-NEXT:    ret i32 [[TMP0]]
  //
  return retIRRef();
}

struct Agg {
  int a;
  long b;
};

// EVAL-NOT: @_Z6retAggv()
// EXPR: @_Z6retAggv()
consteval Agg retAgg() {
  return {13, 17};
}

long test_retAgg() {
  // EVAL-FN-LABEL: @_Z11test_retAggv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[B:%.*]] = alloca i64, align 8
  // EVAL-FN-NEXT:    [[REF_TMP:%.*]] = alloca [[STRUCT_AGG:%.*]], align 8
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = getelementptr inbounds [[STRUCT_AGG]], %struct.Agg* [[REF_TMP]], i32 0, i32 0
  // EVAL-FN-NEXT:    store i32 13, i32* [[TMP0]], align 8
  // EVAL-FN-NEXT:    [[TMP1:%.*]] = getelementptr inbounds [[STRUCT_AGG]], %struct.Agg* [[REF_TMP]], i32 0, i32 1
  // EVAL-FN-NEXT:    store i64 17, i64* [[TMP1]], align 8
  // EVAL-FN-NEXT:    store i64 17, i64* [[B]], align 8
  // EVAL-FN-NEXT:    [[TMP2:%.*]] = load i64, i64* [[B]], align 8
  // EVAL-FN-NEXT:    ret i64 [[TMP2]]
  //
  long b = retAgg().b;
  return b;
}

// EVAL-STATIC: @A = global %struct.Agg { i32 13, i64 17 }, align 8
Agg A = retAgg();

// EVAL-NOT: @_Z9retRefAggv()
// EXPR: @_Z9retRefAggv()
consteval const Agg &retRefAgg() {
  const Agg &tmp = A;
  return A;
}

long test_retRefAgg() {
  // EVAL-FN-LABEL: @_Z14test_retRefAggv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[B:%.*]] = alloca i64, align 8
  // EVAL-FN-NEXT:    [[REF_TMP:%.*]] = alloca [[STRUCT_AGG:%.*]], align 8
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = getelementptr inbounds [[STRUCT_AGG]], %struct.Agg* [[REF_TMP]], i32 0, i32 0
  // EVAL-FN-NEXT:    store i32 13, i32* [[TMP0]], align 8
  // EVAL-FN-NEXT:    [[TMP1:%.*]] = getelementptr inbounds [[STRUCT_AGG]], %struct.Agg* [[REF_TMP]], i32 0, i32 1
  // EVAL-FN-NEXT:    store i64 17, i64* [[TMP1]], align 8
  // EVAL-FN-NEXT:    store i64 17, i64* [[B]], align 8
  // EVAL-FN-NEXT:    [[TMP2:%.*]] = load i64, i64* [[B]], align 8
  // EVAL-FN-NEXT:    ret i64 [[TMP2]]
  //
  long b = retAgg().b;
  return b;
}

// EVAL-NOT: @_Z8is_constv()
// EXPR: @_Z8is_constv()
consteval Agg is_const() {
  return {5, 19 * __builtin_is_constant_evaluated()};
}

long test_is_const() {
  // EVAL-FN-LABEL: @_Z13test_is_constv(
  // EVAL-FN-NEXT:  entry:
  // EVAL-FN-NEXT:    [[B:%.*]] = alloca i64, align 8
  // EVAL-FN-NEXT:    [[REF_TMP:%.*]] = alloca [[STRUCT_AGG:%.*]], align 8
  // EVAL-FN-NEXT:    [[TMP0:%.*]] = getelementptr inbounds [[STRUCT_AGG]], %struct.Agg* [[REF_TMP]], i32 0, i32 0
  // EVAL-FN-NEXT:    store i32 5, i32* [[TMP0]], align 8
  // EVAL-FN-NEXT:    [[TMP1:%.*]] = getelementptr inbounds [[STRUCT_AGG]], %struct.Agg* [[REF_TMP]], i32 0, i32 1
  // EVAL-FN-NEXT:    store i64 19, i64* [[TMP1]], align 8
  // EVAL-FN-NEXT:    store i64 19, i64* [[B]], align 8
  // EVAL-FN-NEXT:    [[TMP2:%.*]] = load i64, i64* [[B]], align 8
  // EVAL-FN-NEXT:    ret i64 [[TMP2]]
  //
  long b = is_const().b;
  return b;
}

// EVAL-NOT: @_ZN7AggCtorC
// EXPR: @_ZN7AggCtorC
struct AggCtor {
  consteval AggCtor(int a = 3, long b = 5) : a(a * a), b(a * b) {}
  int a;
  long b;
};

long test_AggCtor() {
  // CHECK-LABEL: @_Z12test_AggCtorv(
  // CHECK-NEXT:  entry:
  // CHECK-NEXT:    [[I:%.*]] = alloca i32, align 4
  // CHECK-NEXT:    [[C:%.*]] = alloca [[STRUCT_AGGCTOR:%.*]], align 8
  // CHECK-NEXT:    store i32 2, i32* [[I]], align 4
  // CHECK-NEXT:    [[TMP0:%.*]] = getelementptr inbounds [[STRUCT_AGGCTOR]], %struct.AggCtor* [[C]], i32 0, i32 0
  // CHECK-NEXT:    store i32 4, i32* [[TMP0]], align 8
  // CHECK-NEXT:    [[TMP1:%.*]] = getelementptr inbounds [[STRUCT_AGGCTOR]], %struct.AggCtor* [[C]], i32 0, i32 1
  // CHECK-NEXT:    store i64 10, i64* [[TMP1]], align 8
  // CHECK-NEXT:    [[A:%.*]] = getelementptr inbounds [[STRUCT_AGGCTOR]], %struct.AggCtor* [[C]], i32 0, i32 0
  // CHECK-NEXT:    [[TMP2:%.*]] = load i32, i32* [[A]], align 8
  // CHECK-NEXT:    [[CONV:%.*]] = sext i32 [[TMP2]] to i64
  // CHECK-NEXT:    [[B:%.*]] = getelementptr inbounds [[STRUCT_AGGCTOR]], %struct.AggCtor* [[C]], i32 0, i32 1
  // CHECK-NEXT:    [[TMP3:%.*]] = load i64, i64* [[B]], align 8
  // CHECK-NEXT:    [[ADD:%.*]] = add nsw i64 [[CONV]], [[TMP3]]
  // CHECK-NEXT:    ret i64 [[ADD]]
  //
  const int i = 2;
  AggCtor C(i);
  return C.a + C.b;
}
