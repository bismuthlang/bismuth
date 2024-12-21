; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(int + str)" = type { i32, [8 x i8] }

@0 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1
@1 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1
@2 = private unnamed_addr constant [12 x i8] c"hello there\00", align 1
@3 = private unnamed_addr constant [7 x i8] c"Error\0A\00", align 1
@4 = private unnamed_addr constant [4 x i8] c"%s\0A\00", align 1

define %Unit @"programs::enumedit::PrintEnum"(%"(int + str)" %0) {
entry:
  %s = alloca ptr, align 8
  %i = alloca i32, align 4
  %1 = alloca %"(int + str)", align 8
  %e = alloca %"(int + str)", align 8
  store %"(int + str)" %0, ptr %e, align 4
  %e1 = load %"(int + str)", ptr %e, align 4
  store %"(int + str)" %e1, ptr %1, align 4
  %2 = getelementptr %"(int + str)", ptr %1, i32 0, i32 0
  %3 = load i32, ptr %2, align 4
  switch i32 %3, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %4 = getelementptr %"(int + str)", ptr %1, i32 0, i32 1
  %5 = load i32, ptr %4, align 4
  store i32 %5, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %6 = call i32 (ptr, ...) @printf(ptr @0, i32 %i2)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %7 = getelementptr %"(int + str)", ptr %1, i32 0, i32 1
  %8 = load ptr, ptr %7, align 8
  store ptr %8, ptr %s, align 8
  %s3 = load ptr, ptr %s, align 8
  %9 = call i32 (ptr, ...) @printf(ptr @1, ptr %s3)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %1 = alloca %"(int + str)", align 8
  %s = alloca ptr, align 8
  %i = alloca i32, align 4
  %2 = alloca %"(int + str)", align 8
  %a = alloca %"(int + str)", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %3 = getelementptr %"(int + str)", ptr %a, i32 0, i32 0
  store i32 2, ptr %3, align 4
  %4 = getelementptr %"(int + str)", ptr %a, i32 0, i32 1
  store ptr @2, ptr %4, align 8
  %a1 = load %"(int + str)", ptr %a, align 4
  %5 = call %Unit @"programs::enumedit::PrintEnum"(%"(int + str)" %a1)
  %a2 = load %"(int + str)", ptr %a, align 4
  store %"(int + str)" %a2, ptr %2, align 4
  %6 = getelementptr %"(int + str)", ptr %2, i32 0, i32 0
  %7 = load i32, ptr %6, align 4
  switch i32 %7, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %8 = getelementptr %"(int + str)", ptr %2, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  store i32 %9, ptr %i, align 4
  %10 = call i32 (ptr, ...) @printf(ptr @3)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %11 = getelementptr %"(int + str)", ptr %2, i32 0, i32 1
  %12 = load ptr, ptr %11, align 8
  store ptr %12, ptr %s, align 8
  %13 = getelementptr %"(int + str)", ptr %a, i32 0, i32 0
  store i32 1, ptr %13, align 4
  %14 = getelementptr %"(int + str)", ptr %a, i32 0, i32 1
  store i32 10, ptr %14, align 4
  %15 = getelementptr %"(int + str)", ptr %1, i32 0, i32 0
  store i32 1, ptr %15, align 4
  %16 = getelementptr %"(int + str)", ptr %1, i32 0, i32 1
  store i32 10, ptr %16, align 4
  %17 = load %"(int + str)", ptr %1, align 4
  %18 = call %Unit @"programs::enumedit::PrintEnum"(%"(int + str)" %17)
  %s3 = load ptr, ptr %s, align 8
  %19 = call i32 (ptr, ...) @printf(ptr @4, ptr %s3)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %a4 = load %"(int + str)", ptr %a, align 4
  %20 = call %Unit @"programs::enumedit::PrintEnum"(%"(int + str)" %a4)
  %21 = call ptr @malloc(i32 4)
  store i32 0, ptr %21, align 4
  %22 = load ptr, ptr %c, align 8
  %23 = call %Unit @_WriteChannel(ptr %22, ptr %21)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
