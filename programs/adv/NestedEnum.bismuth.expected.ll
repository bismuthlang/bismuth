; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"programs::adv::NestedEnum::Inner" = type { i32, [4 x i8] }
%"programs::adv::NestedEnum::Outer" = type { i32, [8 x i8] }

@0 = private unnamed_addr constant [9 x i8] c"int: %u\0A\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"boolean: %s\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@3 = private unnamed_addr constant [6 x i8] c"false\00", align 1
@4 = private unnamed_addr constant [9 x i8] c"str: %s\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %s = alloca ptr, align 8
  %b = alloca i1, align 1
  %i.0 = alloca i32, align 4
  %1 = alloca %"programs::adv::NestedEnum::Inner", align 8
  %in = alloca %"programs::adv::NestedEnum::Inner", align 8
  %2 = alloca %"programs::adv::NestedEnum::Outer", align 8
  %o = alloca %"programs::adv::NestedEnum::Outer", align 8
  %i = alloca %"programs::adv::NestedEnum::Inner", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = getelementptr %"programs::adv::NestedEnum::Inner", ptr %i, i32 0, i32 0
  store i32 2, ptr %3, align 4
  %4 = getelementptr %"programs::adv::NestedEnum::Inner", ptr %i, i32 0, i32 1
  store i32 5, ptr %4, align 4
  %i1 = load %"programs::adv::NestedEnum::Inner", ptr %i, align 4
  %5 = getelementptr %"programs::adv::NestedEnum::Outer", ptr %o, i32 0, i32 0
  store i32 1, ptr %5, align 4
  %6 = getelementptr %"programs::adv::NestedEnum::Outer", ptr %o, i32 0, i32 1
  store %"programs::adv::NestedEnum::Inner" %i1, ptr %6, align 4
  %o2 = load %"programs::adv::NestedEnum::Outer", ptr %o, align 4
  store %"programs::adv::NestedEnum::Outer" %o2, ptr %2, align 4
  %7 = getelementptr %"programs::adv::NestedEnum::Outer", ptr %2, i32 0, i32 0
  %8 = load i32, ptr %7, align 4
  switch i32 %8, label %match-cont9 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch27
  ]

tagBranch1:                                       ; preds = %entry
  %9 = getelementptr %"programs::adv::NestedEnum::Outer", ptr %2, i32 0, i32 1
  %10 = load %"programs::adv::NestedEnum::Inner", ptr %9, align 4
  store %"programs::adv::NestedEnum::Inner" %10, ptr %in, align 4
  %in3 = load %"programs::adv::NestedEnum::Inner", ptr %in, align 4
  store %"programs::adv::NestedEnum::Inner" %in3, ptr %1, align 4
  %11 = getelementptr %"programs::adv::NestedEnum::Inner", ptr %1, i32 0, i32 0
  %12 = load i32, ptr %11, align 4
  switch i32 %12, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch15
  ]

tagBranch2:                                       ; preds = %tagBranch1
  %13 = getelementptr %"programs::adv::NestedEnum::Inner", ptr %1, i32 0, i32 1
  %14 = load i32, ptr %13, align 4
  store i32 %14, ptr %i.0, align 4
  %i.04 = load i32, ptr %i.0, align 4
  %15 = call i32 (ptr, ...) @printf(ptr @0, i32 %i.04)
  br label %match-cont

tagBranch15:                                      ; preds = %tagBranch1
  %16 = getelementptr %"programs::adv::NestedEnum::Inner", ptr %1, i32 0, i32 1
  %17 = load i1, ptr %16, align 1
  store i1 %17, ptr %b, align 1
  %b6 = load i1, ptr %b, align 1
  %18 = call ptr @"program::#lambda"(i1 %b6)
  %19 = call i32 (ptr, ...) @printf(ptr @1, ptr %18)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch15, %tagBranch2, %tagBranch1
  br label %match-cont9

tagBranch27:                                      ; preds = %entry
  %20 = getelementptr %"programs::adv::NestedEnum::Outer", ptr %2, i32 0, i32 1
  %21 = load ptr, ptr %20, align 8
  store ptr %21, ptr %s, align 8
  %s8 = load ptr, ptr %s, align 8
  %22 = call i32 (ptr, ...) @printf(ptr @4, ptr %s8)
  br label %match-cont9

match-cont9:                                      ; preds = %tagBranch27, %match-cont, %entry
  %23 = call ptr @malloc(i32 4)
  store i32 0, ptr %23, align 4
  %24 = load ptr, ptr %c, align 8
  %25 = call %Unit @_WriteChannel(ptr %24, ptr %23)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

define private ptr @"program::#lambda"(i1 %0) {
entry:
  %b = alloca i1, align 1
  store i1 %0, ptr %b, align 1
  %b1 = load i1, ptr %b, align 1
  br i1 %b1, label %then, label %else

then:                                             ; preds = %entry
  ret ptr @2

else:                                             ; preds = %entry
  ret ptr @3
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
