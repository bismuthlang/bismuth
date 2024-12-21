; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(boolean + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [13 x i8] c"integer: %u\0A\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"boolean: %s\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@3 = private unnamed_addr constant [6 x i8] c"false\00", align 1

define %Unit @"programs::adv::enumPassing::test"(ptr %0) {
entry:
  %b = alloca i1, align 1
  %i = alloca i32, align 4
  %1 = alloca %"(boolean + int)", align 8
  %sum = alloca %"(boolean + int)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load %"(boolean + int)", ptr %3, align 4
  %5 = call %Unit @free(ptr %3)
  store %"(boolean + int)" %4, ptr %sum, align 4
  %sum1 = load %"(boolean + int)", ptr %sum, align 4
  store %"(boolean + int)" %sum1, ptr %1, align 4
  %6 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 0
  %7 = load %"(boolean + int)", ptr %6, align 4
  switch %"(boolean + int)" %7, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %entry
  %8 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  store i32 %9, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %10 = call i32 (ptr, ...) @printf(ptr @0, i32 %i2)
  br label %match-cont

tagBranch1:                                       ; preds = %entry
  %11 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 1
  %12 = load i1, ptr %11, align 1
  store i1 %12, ptr %b, align 1
  %b3 = load i1, ptr %b, align 1
  %13 = call ptr @"programs::adv::enumPassing::test::#lambda"(i1 %b3)
  %14 = call i32 (ptr, ...) @printf(ptr @1, ptr %13)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %1 = alloca %"(boolean + int)", align 8
  %t = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = call ptr @_Execute(ptr @"programs::adv::enumPassing::test")
  store ptr %2, ptr %t, align 8
  %3 = getelementptr i32, ptr %1, i32 0, i32 0
  store i32 2, ptr %3, align 4
  %4 = getelementptr %"(boolean + int)", ptr %1, i32 0, i32 1
  store i32 5, ptr %4, align 4
  %5 = load %"(boolean + int)", ptr %1, align 4
  %6 = call ptr @malloc(i32 8)
  store %"(boolean + int)" %5, ptr %6, align 4
  %7 = load ptr, ptr %t, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  %9 = call ptr @malloc(i32 4)
  store i32 0, ptr %9, align 4
  %10 = load ptr, ptr %c, align 8
  %11 = call %Unit @_WriteChannel(ptr %10, ptr %9)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

define private ptr @"programs::adv::enumPassing::test::#lambda"(i1 %0) {
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

declare ptr @_Execute(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
