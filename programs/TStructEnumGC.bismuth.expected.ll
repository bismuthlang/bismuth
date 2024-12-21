; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%TIBB = type { ptr, ptr }
%ETIBBOB = type { i32, [16 x i8] }

@0 = private unnamed_addr constant [25 x i8] c"%s = {b1 : %u, b2 : %u}\0A\00", align 1
@1 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@2 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@4 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@5 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@6 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1
@7 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define %Unit @printTIBB(ptr %0, %TIBB %1) {
entry:
  %b = alloca %TIBB, align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store %TIBB %1, ptr %b, align 8
  %name1 = load ptr, ptr %name, align 8
  %2 = getelementptr %TIBB, ptr %b, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = load ptr, ptr %3, align 8
  %5 = load i32, ptr %4, align 4
  %6 = getelementptr %TIBB, ptr %b, i32 0, i32 1
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = load i32, ptr %8, align 4
  %10 = call %Unit (ptr, ...) @printf(ptr @0, ptr %name1, i32 %5, i32 %9)
  ret %Unit zeroinitializer
}

define %Unit @foo(ptr %0) {
entry:
  %t.0 = alloca i32, align 4
  %i = alloca i32, align 4
  %t = alloca i32, align 4
  %iPtr = alloca %TIBB, align 8
  %1 = alloca %ETIBBOB, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load %ETIBBOB, ptr %3, align 4
  %5 = call %Unit @free(ptr %3)
  store %ETIBBOB %4, ptr %1, align 4
  %6 = getelementptr %ETIBBOB, ptr %1, i32 0, i32 0
  %7 = load i32, ptr %6, align 4
  switch i32 %7, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %8 = getelementptr %ETIBBOB, ptr %1, i32 0, i32 1
  %9 = load %TIBB, ptr %8, align 8
  store %TIBB %9, ptr %iPtr, align 8
  %iPtr1 = load %TIBB, ptr %iPtr, align 8
  %10 = call %Unit @printTIBB(ptr @1, %TIBB %iPtr1)
  %11 = getelementptr %TIBB, ptr %iPtr, i32 0, i32 0
  %12 = load ptr, ptr %11, align 8
  %13 = load ptr, ptr %12, align 8
  store i32 7, ptr %13, align 4
  %iPtr2 = load %TIBB, ptr %iPtr, align 8
  %14 = call %Unit @printTIBB(ptr @2, %TIBB %iPtr2)
  %15 = sub nsw i32 0, 1
  %16 = call ptr @malloc(i32 4)
  store i32 %15, ptr %16, align 4
  %17 = load ptr, ptr %c, align 8
  %18 = call %Unit @_WriteChannel(ptr %17, ptr %16)
  %19 = load ptr, ptr %c, align 8
  %20 = call ptr @_ReadLinearChannel(ptr %19)
  %21 = load i32, ptr %20, align 4
  %22 = call %Unit @free(ptr %20)
  store i32 %21, ptr %t, align 4
  %iPtr3 = load %TIBB, ptr %iPtr, align 8
  %23 = call %Unit @printTIBB(ptr @3, %TIBB %iPtr3)
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %24 = getelementptr %ETIBBOB, ptr %1, i32 0, i32 1
  %25 = load i32, ptr %24, align 4
  store i32 %25, ptr %i, align 4
  %26 = sub nsw i32 0, 1
  %27 = call ptr @malloc(i32 4)
  store i32 %26, ptr %27, align 4
  %28 = load ptr, ptr %c, align 8
  %29 = call %Unit @_WriteChannel(ptr %28, ptr %27)
  %30 = load ptr, ptr %c, align 8
  %31 = call ptr @_ReadLinearChannel(ptr %30)
  %32 = load i32, ptr %31, align 4
  %33 = call %Unit @free(ptr %31)
  store i32 %32, ptr %t.0, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u = alloca i32, align 4
  %1 = alloca %ETIBBOB, align 8
  %2 = alloca %TIBB, align 8
  %a = alloca ptr, align 8
  %tibb = alloca %TIBB, align 8
  %shared = alloca ptr, align 8
  %ctr = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %ctr, align 4
  br i1 true, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %3 = call ptr @_Execute(ptr @foo)
  store ptr %3, ptr %a, align 8
  %4 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %4, align 4
  %5 = call ptr @GC_malloc(i64 8)
  store ptr %4, ptr %5, align 8
  store ptr %5, ptr %shared, align 8
  %shared1 = load ptr, ptr %shared, align 8
  %6 = call ptr @GC_malloc(i64 4)
  store i32 6, ptr %6, align 4
  %7 = call ptr @GC_malloc(i64 8)
  store ptr %6, ptr %7, align 8
  %8 = getelementptr %TIBB, ptr %2, i32 0, i32 0
  store ptr %shared1, ptr %8, align 8
  %9 = getelementptr %TIBB, ptr %2, i32 0, i32 1
  store ptr %7, ptr %9, align 8
  %10 = load %TIBB, ptr %2, align 8
  store %TIBB %10, ptr %tibb, align 8
  %11 = getelementptr %TIBB, ptr %tibb, i32 0, i32 0
  %shared2 = load ptr, ptr %shared, align 8
  store ptr %shared2, ptr %11, align 8
  %tibb3 = load %TIBB, ptr %tibb, align 8
  %12 = call %Unit @printTIBB(ptr @4, %TIBB %tibb3)
  %tibb4 = load %TIBB, ptr %tibb, align 8
  %13 = call ptr @_address_map_create()
  %14 = call %TIBB @_clone_TIBB(%TIBB %tibb4, ptr %13)
  %15 = call %Unit @_address_map_delete(ptr %13)
  %16 = getelementptr %ETIBBOB, ptr %1, i32 0, i32 0
  store i32 1, ptr %16, align 4
  %17 = getelementptr %ETIBBOB, ptr %1, i32 0, i32 1
  store %TIBB %14, ptr %17, align 8
  %18 = load %ETIBBOB, ptr %1, align 4
  %19 = call ptr @malloc(i32 20)
  store %ETIBBOB %18, ptr %19, align 4
  %20 = load ptr, ptr %a, align 8
  %21 = call %Unit @_WriteChannel(ptr %20, ptr %19)
  %22 = load ptr, ptr %a, align 8
  %23 = call ptr @_ReadLinearChannel(ptr %22)
  %24 = load i32, ptr %23, align 4
  %25 = call %Unit @free(ptr %23)
  store i32 %24, ptr %u, align 4
  %tibb5 = load %TIBB, ptr %tibb, align 8
  %26 = call %Unit @printTIBB(ptr @5, %TIBB %tibb5)
  %shared6 = load ptr, ptr %shared, align 8
  %27 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %27, align 4
  store ptr %27, ptr %shared6, align 8
  %tibb7 = load %TIBB, ptr %tibb, align 8
  %28 = call %Unit @printTIBB(ptr @6, %TIBB %tibb7)
  %29 = sub nsw i32 0, 1
  %30 = call ptr @malloc(i32 4)
  store i32 %29, ptr %30, align 4
  %31 = load ptr, ptr %a, align 8
  %32 = call %Unit @_WriteChannel(ptr %31, ptr %30)
  %ctr8 = load i32, ptr %ctr, align 4
  %33 = add nsw i32 %ctr8, 1
  store i32 %33, ptr %ctr, align 4
  %34 = call i32 @GC_get_heap_size()
  %35 = call %Unit (ptr, ...) @printf(ptr @7, i32 %34)
  br i1 true, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %36 = call ptr @malloc(i32 4)
  store i32 0, ptr %36, align 4
  %37 = load ptr, ptr %c, align 8
  %38 = call %Unit @_WriteChannel(ptr %37, ptr %36)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

declare i32 @GC_get_heap_size()

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare ptr @GC_malloc(i64)

declare ptr @_address_map_create()

define private %TIBB @_clone_TIBB(%TIBB %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca %TIBB, align 8
  store %TIBB %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = getelementptr %TIBB, ptr %v, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = load ptr, ptr %m, align 8
  %5 = call ptr @"_clone_Box<Box<int>>"(ptr %3, ptr %4)
  store ptr %5, ptr %2, align 8
  %6 = getelementptr %TIBB, ptr %v, i32 0, i32 1
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @"_clone_Box<Box<int>>"(ptr %7, ptr %8)
  store ptr %9, ptr %6, align 8
  %10 = load %TIBB, ptr %v, align 8
  ret %TIBB %10
}

define private ptr @"_clone_Box<Box<int>>"(ptr %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca ptr, align 8
  store ptr %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = load ptr, ptr %v, align 8
  %3 = load ptr, ptr %m, align 8
  %4 = call ptr @_address_map_has(ptr %3, ptr %2)
  %5 = icmp ne ptr %4, null
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  br label %if-cont

else:                                             ; preds = %entry
  %6 = load ptr, ptr %m, align 8
  %7 = load ptr, ptr %v, align 8
  %8 = load ptr, ptr %7, align 8
  %9 = call ptr @"_clone_Box<int>"(ptr %8, ptr %6)
  %10 = call ptr @GC_malloc(i64 8)
  store ptr %9, ptr %10, align 8
  %11 = load ptr, ptr %m, align 8
  %12 = call %Unit @_address_map_put(ptr %11, ptr %2, ptr %10)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %10, %else ]
  ret ptr %phi
}

declare ptr @_address_map_has(ptr, ptr)

define private ptr @"_clone_Box<int>"(ptr %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca ptr, align 8
  store ptr %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = load ptr, ptr %v, align 8
  %3 = load ptr, ptr %m, align 8
  %4 = call ptr @_address_map_has(ptr %3, ptr %2)
  %5 = icmp ne ptr %4, null
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  br label %if-cont

else:                                             ; preds = %entry
  %6 = load ptr, ptr %m, align 8
  %7 = load ptr, ptr %v, align 8
  %8 = load i32, ptr %7, align 4
  %9 = call ptr @GC_malloc(i64 8)
  store i32 %8, ptr %9, align 4
  %10 = load ptr, ptr %m, align 8
  %11 = call %Unit @_address_map_put(ptr %10, ptr %2, ptr %9)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %9, %else ]
  ret ptr %phi
}

declare %Unit @_address_map_put(ptr, ptr, ptr)

declare %Unit @_address_map_delete(ptr)
