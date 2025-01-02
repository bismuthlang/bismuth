; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%TIBB = type { ptr, ptr }

@0 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@2 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@4 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@5 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1
@6 = private unnamed_addr constant [4 x i8] c"%u\0A\00", align 1

define %Unit @printTIBB(ptr %0, %TIBB %1) {
entry:
  %b = alloca %TIBB, align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store %TIBB %1, ptr %b, align 8
  ret %Unit zeroinitializer
}

define %Unit @foo(ptr %0) {
entry:
  %t = alloca i32, align 4
  %iPtr = alloca %TIBB, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load %TIBB, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store %TIBB %3, ptr %iPtr, align 8
  %iPtr1 = load %TIBB, ptr %iPtr, align 8
  %5 = call %Unit @printTIBB(ptr @0, %TIBB %iPtr1)
  %6 = getelementptr %TIBB, ptr %iPtr, i32 0, i32 0
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %7, align 8
  store i32 7, ptr %8, align 4
  %iPtr2 = load %TIBB, ptr %iPtr, align 8
  %9 = call %Unit @printTIBB(ptr @1, %TIBB %iPtr2)
  %10 = sub nsw i32 0, 1
  %11 = call ptr @malloc(i32 4)
  store i32 %10, ptr %11, align 4
  %12 = load ptr, ptr %c, align 8
  %13 = call %Unit @_WriteChannel(ptr %12, ptr %11)
  %14 = load ptr, ptr %c, align 8
  %15 = call ptr @_ReadLinearChannel(ptr %14)
  %16 = load i32, ptr %15, align 4
  %17 = call %Unit @free(ptr %15)
  store i32 %16, ptr %t, align 4
  %iPtr3 = load %TIBB, ptr %iPtr, align 8
  %18 = call %Unit @printTIBB(ptr @2, %TIBB %iPtr3)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u = alloca i32, align 4
  %1 = alloca %TIBB, align 8
  %a = alloca ptr, align 8
  %tibb = alloca %TIBB, align 8
  %shared = alloca ptr, align 8
  %ctr = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %ctr, align 4
  br i1 true, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %2 = call ptr @_Execute(ptr @foo)
  store ptr %2, ptr %a, align 8
  %3 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %3, align 4
  %4 = call ptr @GC_malloc(i64 8)
  store ptr %3, ptr %4, align 8
  store ptr %4, ptr %shared, align 8
  %shared1 = load ptr, ptr %shared, align 8
  %5 = call ptr @GC_malloc(i64 4)
  store i32 6, ptr %5, align 4
  %6 = call ptr @GC_malloc(i64 8)
  store ptr %5, ptr %6, align 8
  %7 = getelementptr %TIBB, ptr %1, i32 0, i32 0
  store ptr %shared1, ptr %7, align 8
  %8 = getelementptr %TIBB, ptr %1, i32 0, i32 1
  store ptr %6, ptr %8, align 8
  %9 = load %TIBB, ptr %1, align 8
  store %TIBB %9, ptr %tibb, align 8
  %10 = getelementptr %TIBB, ptr %tibb, i32 0, i32 0
  %shared2 = load ptr, ptr %shared, align 8
  store ptr %shared2, ptr %10, align 8
  %tibb3 = load %TIBB, ptr %tibb, align 8
  %11 = call %Unit @printTIBB(ptr @3, %TIBB %tibb3)
  %tibb4 = load %TIBB, ptr %tibb, align 8
  %12 = call ptr @_address_map_create()
  %13 = call %TIBB @_clone_TIBB(%TIBB %tibb4, ptr %12)
  %14 = call %Unit @_address_map_delete(ptr %12)
  %15 = call ptr @malloc(i32 16)
  store %TIBB %13, ptr %15, align 8
  %16 = load ptr, ptr %a, align 8
  %17 = call %Unit @_WriteChannel(ptr %16, ptr %15)
  %18 = load ptr, ptr %a, align 8
  %19 = call ptr @_ReadLinearChannel(ptr %18)
  %20 = load i32, ptr %19, align 4
  %21 = call %Unit @free(ptr %19)
  store i32 %20, ptr %u, align 4
  %tibb5 = load %TIBB, ptr %tibb, align 8
  %22 = call %Unit @printTIBB(ptr @4, %TIBB %tibb5)
  %shared6 = load ptr, ptr %shared, align 8
  %23 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %23, align 4
  store ptr %23, ptr %shared6, align 8
  %tibb7 = load %TIBB, ptr %tibb, align 8
  %24 = call %Unit @printTIBB(ptr @5, %TIBB %tibb7)
  %25 = sub nsw i32 0, 1
  %26 = call ptr @malloc(i32 4)
  store i32 %25, ptr %26, align 4
  %27 = load ptr, ptr %a, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  %ctr8 = load i32, ptr %ctr, align 4
  %29 = add nsw i32 %ctr8, 1
  store i32 %29, ptr %ctr, align 4
  %30 = call i32 @GC_get_heap_size()
  %31 = call %Unit (ptr, ...) @printf(ptr @6, i32 %30)
  br i1 true, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %32 = call ptr @malloc(i32 4)
  store i32 0, ptr %32, align 4
  %33 = load ptr, ptr %c, align 8
  %34 = call %Unit @_WriteChannel(ptr %33, ptr %32)
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
  %6 = load ptr, ptr %v, align 8
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @"_clone_Box<int>"(ptr %7, ptr %8)
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
  %6 = load ptr, ptr %v, align 8
  %7 = load i32, ptr %6, align 4
  %8 = load ptr, ptr %m, align 8
  %9 = call ptr @GC_malloc(i64 8)
  store i32 %7, ptr %9, align 4
  %10 = load ptr, ptr %m, align 8
  %11 = call %Unit @_address_map_put(ptr %10, ptr %2, ptr %9)
  br label %if-cont

if-cont:                                          ; preds = %else, %then
  %phi = phi ptr [ %4, %then ], [ %9, %else ]
  ret ptr %phi
}

declare %Unit @_address_map_put(ptr, ptr, ptr)

declare %Unit @_address_map_delete(ptr)
