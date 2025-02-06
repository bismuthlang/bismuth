; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%TIBB = type { ptr, ptr, %IB }
%IB = type { ptr }

@0 = private unnamed_addr constant [31 x i8] c"%s = {b1 : %u@%p, b2 : %u@%p}\0A\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"b (orig/5;6)\00", align 1
@2 = private unnamed_addr constant [13 x i8] c"b (orig/9;6)\00", align 1

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
  %6 = getelementptr %TIBB, ptr %b, i32 0, i32 0
  %7 = load ptr, ptr %6, align 8
  %8 = getelementptr %TIBB, ptr %b, i32 0, i32 1
  %9 = load ptr, ptr %8, align 8
  %10 = load ptr, ptr %9, align 8
  %11 = load i32, ptr %10, align 4
  %12 = getelementptr %TIBB, ptr %b, i32 0, i32 1
  %13 = load ptr, ptr %12, align 8
  %14 = call %Unit (ptr, ...) @printf(ptr @0, ptr %name1, i32 %5, ptr %7, i32 %11, ptr %13)
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %tibb23 = alloca %TIBB, align 8
  %tibb = alloca %TIBB, align 8
  %1 = alloca %TIBB, align 8
  %2 = alloca %IB, align 8
  %shared = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
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
  %7 = call ptr @GC_malloc(i64 4)
  store i32 1, ptr %7, align 4
  %8 = getelementptr %IB, ptr %2, i32 0, i32 0
  store ptr %7, ptr %8, align 8
  %9 = load %IB, ptr %2, align 8
  %10 = getelementptr %TIBB, ptr %1, i32 0, i32 0
  store ptr %shared1, ptr %10, align 8
  %11 = getelementptr %TIBB, ptr %1, i32 0, i32 1
  store ptr %6, ptr %11, align 8
  %12 = getelementptr %TIBB, ptr %1, i32 0, i32 2
  store %IB %9, ptr %12, align 8
  %13 = load %TIBB, ptr %1, align 8
  store %TIBB %13, ptr %tibb, align 8
  %tibb2 = load %TIBB, ptr %tibb, align 8
  %14 = call ptr @_address_map_create()
  %15 = call %TIBB @_clone_TIBB(%TIBB %tibb2, ptr %14)
  %16 = call %Unit @_address_map_delete(ptr %14)
  store %TIBB %15, ptr %tibb23, align 8
  %shared4 = load ptr, ptr %shared, align 8
  %17 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %17, align 4
  store ptr %17, ptr %shared4, align 8
  %tibb25 = load %TIBB, ptr %tibb23, align 8
  %18 = call %Unit @printTIBB(ptr @1, %TIBB %tibb25)
  %tibb6 = load %TIBB, ptr %tibb, align 8
  %19 = call %Unit @printTIBB(ptr @2, %TIBB %tibb6)
  %20 = call ptr @malloc(i32 4)
  store i32 0, ptr %20, align 4
  %21 = load ptr, ptr %c, align 8
  %22 = call %Unit @_WriteChannel(ptr %21, ptr %20)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

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

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
