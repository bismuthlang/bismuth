; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [9 x i8] c"%s = %u\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"%s = %u\0A\00", align 1
@2 = private unnamed_addr constant [14 x i8] c"iPtr (orig/5)\00", align 1
@3 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@4 = private unnamed_addr constant [13 x i8] c"iPtr (mod/7)\00", align 1
@5 = private unnamed_addr constant [11 x i8] c"b (orig/5)\00", align 1
@6 = private unnamed_addr constant [11 x i8] c"b (orig/5)\00", align 1
@7 = private unnamed_addr constant [11 x i8] c"b (orig/9)\00", align 1

define %Unit @printBoxInt(ptr %0, ptr %1) {
entry:
  %b = alloca ptr, align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store ptr %1, ptr %b, align 8
  %name1 = load ptr, ptr %name, align 8
  %b2 = load ptr, ptr %b, align 8
  %2 = load i32, ptr %b2, align 4
  %3 = call %Unit (ptr, ...) @printf(ptr @0, ptr %name1, i32 %2)
  ret %Unit zeroinitializer
}

define %Unit @printBoxBoxInt(ptr %0, ptr %1) {
entry:
  %b = alloca ptr, align 8
  %name = alloca ptr, align 8
  store ptr %0, ptr %name, align 8
  store ptr %1, ptr %b, align 8
  %name1 = load ptr, ptr %name, align 8
  %b2 = load ptr, ptr %b, align 8
  %2 = load ptr, ptr %b2, align 8
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit (ptr, ...) @printf(ptr @1, ptr %name1, i32 %3)
  ret %Unit zeroinitializer
}

define %Unit @foo(ptr %0) {
entry:
  %t = alloca i32, align 4
  %iPtr = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %iPtr, align 8
  %iPtr1 = load ptr, ptr %iPtr, align 8
  %5 = call %Unit @printBoxBoxInt(ptr @2, ptr %iPtr1)
  %iPtr2 = load ptr, ptr %iPtr, align 8
  %6 = load ptr, ptr %iPtr2, align 8
  store i32 7, ptr %6, align 4
  %iPtr3 = load ptr, ptr %iPtr, align 8
  %7 = call %Unit @printBoxBoxInt(ptr @3, ptr %iPtr3)
  %8 = sub nsw i32 0, 1
  %9 = call ptr @malloc(i32 4)
  store i32 %8, ptr %9, align 4
  %10 = load ptr, ptr %c, align 8
  %11 = call %Unit @_WriteChannel(ptr %10, ptr %9)
  %12 = load ptr, ptr %c, align 8
  %13 = call ptr @_ReadLinearChannel(ptr %12)
  %14 = load i32, ptr %13, align 4
  %15 = call %Unit @free(ptr %13)
  store i32 %14, ptr %t, align 4
  %iPtr4 = load ptr, ptr %iPtr, align 8
  %16 = call %Unit @printBoxBoxInt(ptr @4, ptr %iPtr4)
  ret %Unit zeroinitializer
}

define %Unit @bar(ptr %0) {
entry:
  %iPtr = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load ptr, ptr %2, align 8
  %4 = call %Unit @free(ptr %2)
  store ptr %3, ptr %iPtr, align 8
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %u = alloca i32, align 4
  %b = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @foo)
  store ptr %1, ptr %a, align 8
  %2 = call ptr @GC_malloc(i64 4)
  store i32 5, ptr %2, align 4
  %3 = call ptr @GC_malloc(i64 8)
  store ptr %2, ptr %3, align 8
  store ptr %3, ptr %b, align 8
  %b1 = load ptr, ptr %b, align 8
  %4 = call %Unit @printBoxBoxInt(ptr @5, ptr %b1)
  %b2 = load ptr, ptr %b, align 8
  %5 = call ptr @_address_map_create()
  %6 = call ptr @"_clone_Box<Box<int>>"(ptr %b2, ptr %5)
  %7 = call %Unit @_address_map_delete(ptr %5)
  %8 = call ptr @malloc(i32 8)
  store ptr %6, ptr %8, align 8
  %9 = load ptr, ptr %a, align 8
  %10 = call %Unit @_WriteChannel(ptr %9, ptr %8)
  %11 = load ptr, ptr %a, align 8
  %12 = call ptr @_ReadLinearChannel(ptr %11)
  %13 = load i32, ptr %12, align 4
  %14 = call %Unit @free(ptr %12)
  store i32 %13, ptr %u, align 4
  %b3 = load ptr, ptr %b, align 8
  %15 = call %Unit @printBoxBoxInt(ptr @6, ptr %b3)
  %b4 = load ptr, ptr %b, align 8
  %16 = call ptr @GC_malloc(i64 4)
  store i32 9, ptr %16, align 4
  store ptr %16, ptr %b4, align 8
  %b5 = load ptr, ptr %b, align 8
  %17 = call %Unit @printBoxBoxInt(ptr @7, ptr %b5)
  %18 = sub nsw i32 0, 1
  %19 = call ptr @malloc(i32 4)
  store i32 %18, ptr %19, align 4
  %20 = load ptr, ptr %a, align 8
  %21 = call %Unit @_WriteChannel(ptr %20, ptr %19)
  %22 = call ptr @malloc(i32 4)
  store i32 0, ptr %22, align 4
  %23 = load ptr, ptr %c, align 8
  %24 = call %Unit @_WriteChannel(ptr %23, ptr %22)
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
