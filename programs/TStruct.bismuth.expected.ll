; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%TIBB = type { ptr, ptr, %IB }
%IB = type { ptr }

@0 = private unnamed_addr constant [25 x i8] c"%s = {b1 : %u, b2 : %u}\0A\00", align 1
@1 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@2 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@4 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@5 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@6 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@7 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1
@8 = private unnamed_addr constant [8 x i8] c"------\0A\00", align 1
@9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@10 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@11 = private unnamed_addr constant [13 x i8] c"b (orig/5;5)\00", align 1
@12 = private unnamed_addr constant [13 x i8] c"b (orig/9;9)\00", align 1

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
  %5 = call %Unit @printTIBB(ptr @1, %TIBB %iPtr1)
  %6 = getelementptr %TIBB, ptr %iPtr, i32 0, i32 0
  %7 = load ptr, ptr %6, align 8
  %8 = load ptr, ptr %7, align 8
  store i32 7, ptr %8, align 4
  %iPtr2 = load %TIBB, ptr %iPtr, align 8
  %9 = call %Unit @printTIBB(ptr @2, %TIBB %iPtr2)
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
  %18 = call %Unit @printTIBB(ptr @3, %TIBB %iPtr3)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u.0 = alloca i32, align 4
  %tibb.0 = alloca %TIBB, align 8
  %1 = alloca %TIBB, align 8
  %2 = alloca %IB, align 8
  %shared.0 = alloca ptr, align 8
  %a.0 = alloca ptr, align 8
  %u = alloca i32, align 4
  %tibb = alloca %TIBB, align 8
  %3 = alloca %TIBB, align 8
  %4 = alloca %IB, align 8
  %shared = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %5 = call ptr @_Execute(ptr @foo)
  store ptr %5, ptr %a, align 8
  %6 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %6, align 4
  %7 = call ptr @GC_malloc(i64 8)
  store ptr %6, ptr %7, align 8
  store ptr %7, ptr %shared, align 8
  %shared1 = load ptr, ptr %shared, align 8
  %8 = call ptr @GC_malloc(i64 4)
  store i32 6, ptr %8, align 4
  %9 = call ptr @GC_malloc(i64 8)
  store ptr %8, ptr %9, align 8
  %10 = call ptr @GC_malloc(i64 4)
  store i32 1, ptr %10, align 4
  %11 = getelementptr %IB, ptr %4, i32 0, i32 0
  store ptr %10, ptr %11, align 8
  %12 = load %IB, ptr %4, align 8
  %13 = getelementptr %TIBB, ptr %3, i32 0, i32 0
  store ptr %shared1, ptr %13, align 8
  %14 = getelementptr %TIBB, ptr %3, i32 0, i32 1
  store ptr %9, ptr %14, align 8
  %15 = getelementptr %TIBB, ptr %3, i32 0, i32 2
  store %IB %12, ptr %15, align 8
  %16 = load %TIBB, ptr %3, align 8
  store %TIBB %16, ptr %tibb, align 8
  %17 = getelementptr %TIBB, ptr %tibb, i32 0, i32 0
  %shared2 = load ptr, ptr %shared, align 8
  store ptr %shared2, ptr %17, align 8
  %18 = call %Unit (ptr, ...) @printf(ptr @4)
  %tibb3 = load %TIBB, ptr %tibb, align 8
  %19 = call %Unit @printTIBB(ptr @5, %TIBB %tibb3)
  %tibb4 = load %TIBB, ptr %tibb, align 8
  %20 = call ptr @_address_map_create()
  %21 = call %TIBB @_clone_TIBB(%TIBB %tibb4, ptr %20)
  %22 = call %Unit @_address_map_delete(ptr %20)
  %23 = call ptr @malloc(i32 24)
  store %TIBB %21, ptr %23, align 8
  %24 = load ptr, ptr %a, align 8
  %25 = call %Unit @_WriteChannel(ptr %24, ptr %23)
  %26 = load ptr, ptr %a, align 8
  %27 = call ptr @_ReadLinearChannel(ptr %26)
  %28 = load i32, ptr %27, align 4
  %29 = call %Unit @free(ptr %27)
  store i32 %28, ptr %u, align 4
  %tibb5 = load %TIBB, ptr %tibb, align 8
  %30 = call %Unit @printTIBB(ptr @6, %TIBB %tibb5)
  %shared6 = load ptr, ptr %shared, align 8
  %31 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %31, align 4
  store ptr %31, ptr %shared6, align 8
  %tibb7 = load %TIBB, ptr %tibb, align 8
  %32 = call %Unit @printTIBB(ptr @7, %TIBB %tibb7)
  %33 = sub nsw i32 0, 1
  %34 = call ptr @malloc(i32 4)
  store i32 %33, ptr %34, align 4
  %35 = load ptr, ptr %a, align 8
  %36 = call %Unit @_WriteChannel(ptr %35, ptr %34)
  %37 = call %Unit (ptr, ...) @printf(ptr @8)
  %38 = call ptr @_Execute(ptr @foo)
  store ptr %38, ptr %a.0, align 8
  %39 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %39, align 4
  %40 = call ptr @GC_malloc(i64 8)
  store ptr %39, ptr %40, align 8
  store ptr %40, ptr %shared.0, align 8
  %shared.08 = load ptr, ptr %shared.0, align 8
  %shared.09 = load ptr, ptr %shared.0, align 8
  %41 = call ptr @GC_malloc(i64 4)
  store i32 1, ptr %41, align 4
  %42 = getelementptr %IB, ptr %2, i32 0, i32 0
  store ptr %41, ptr %42, align 8
  %43 = load %IB, ptr %2, align 8
  %44 = getelementptr %TIBB, ptr %1, i32 0, i32 0
  store ptr %shared.08, ptr %44, align 8
  %45 = getelementptr %TIBB, ptr %1, i32 0, i32 1
  store ptr %shared.09, ptr %45, align 8
  %46 = getelementptr %TIBB, ptr %1, i32 0, i32 2
  store %IB %43, ptr %46, align 8
  %47 = load %TIBB, ptr %1, align 8
  store %TIBB %47, ptr %tibb.0, align 8
  %48 = getelementptr %TIBB, ptr %tibb.0, i32 0, i32 0
  %shared.010 = load ptr, ptr %shared.0, align 8
  store ptr %shared.010, ptr %48, align 8
  %49 = call %Unit (ptr, ...) @printf(ptr @9)
  %tibb.011 = load %TIBB, ptr %tibb.0, align 8
  %50 = call %Unit @printTIBB(ptr @10, %TIBB %tibb.011)
  %tibb.012 = load %TIBB, ptr %tibb.0, align 8
  %51 = call ptr @_address_map_create()
  %52 = call %TIBB @_clone_TIBB(%TIBB %tibb.012, ptr %51)
  %53 = call %Unit @_address_map_delete(ptr %51)
  %54 = call ptr @malloc(i32 24)
  store %TIBB %52, ptr %54, align 8
  %55 = load ptr, ptr %a.0, align 8
  %56 = call %Unit @_WriteChannel(ptr %55, ptr %54)
  %57 = load ptr, ptr %a.0, align 8
  %58 = call ptr @_ReadLinearChannel(ptr %57)
  %59 = load i32, ptr %58, align 4
  %60 = call %Unit @free(ptr %58)
  store i32 %59, ptr %u.0, align 4
  %tibb.013 = load %TIBB, ptr %tibb.0, align 8
  %61 = call %Unit @printTIBB(ptr @11, %TIBB %tibb.013)
  %shared.014 = load ptr, ptr %shared.0, align 8
  %62 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %62, align 4
  store ptr %62, ptr %shared.014, align 8
  %tibb.015 = load %TIBB, ptr %tibb.0, align 8
  %63 = call %Unit @printTIBB(ptr @12, %TIBB %tibb.015)
  %64 = sub nsw i32 0, 1
  %65 = call ptr @malloc(i32 4)
  store i32 %64, ptr %65, align 4
  %66 = load ptr, ptr %a.0, align 8
  %67 = call %Unit @_WriteChannel(ptr %66, ptr %65)
  %68 = call ptr @malloc(i32 4)
  store i32 0, ptr %68, align 4
  %69 = load ptr, ptr %c, align 8
  %70 = call %Unit @_WriteChannel(ptr %69, ptr %68)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

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
  %10 = getelementptr %TIBB, ptr %v, i32 0, i32 2
  %11 = load %IB, ptr %10, align 8
  %12 = load ptr, ptr %m, align 8
  %13 = call %IB @_clone_IB(%IB %11, ptr %12)
  store %IB %13, ptr %10, align 8
  %14 = load %TIBB, ptr %v, align 8
  ret %TIBB %14
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

define private %IB @_clone_IB(%IB %0, ptr %1) {
entry:
  %m = alloca ptr, align 8
  %v = alloca %IB, align 8
  store %IB %0, ptr %v, align 8
  store ptr %1, ptr %m, align 8
  %2 = getelementptr %IB, ptr %v, i32 0, i32 0
  %3 = load ptr, ptr %2, align 8
  %4 = load ptr, ptr %m, align 8
  %5 = call ptr @"_clone_Box<int>"(ptr %3, ptr %4)
  store ptr %5, ptr %2, align 8
  %6 = load %IB, ptr %v, align 8
  ret %IB %6
}

declare %Unit @_address_map_delete(ptr)
