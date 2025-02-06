; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [9 x i8] c"%s = %u\0A\00", align 1
@1 = private unnamed_addr constant [9 x i8] c"recv %u\0A\00", align 1
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
  %5 = call %Unit (ptr, ...) @printf(ptr @1, ptr %iPtr1)
  %iPtr2 = load ptr, ptr %iPtr, align 8
  %6 = call %Unit @printBoxInt(ptr @2, ptr %iPtr2)
  %iPtr3 = load ptr, ptr %iPtr, align 8
  store i32 7, ptr %iPtr3, align 4
  %iPtr4 = load ptr, ptr %iPtr, align 8
  %7 = call %Unit @printBoxInt(ptr @3, ptr %iPtr4)
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
  %iPtr5 = load ptr, ptr %iPtr, align 8
  %16 = call %Unit @printBoxInt(ptr @4, ptr %iPtr5)
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
  store ptr %2, ptr %b, align 8
  %b1 = load ptr, ptr %b, align 8
  %3 = call %Unit @printBoxInt(ptr @5, ptr %b1)
  %b2 = load ptr, ptr %b, align 8
  %4 = call ptr @_address_map_create()
  %5 = call ptr @"_clone_Box<int>"(ptr %b2, ptr %4)
  %6 = call %Unit @_address_map_delete(ptr %4)
  %7 = call ptr @malloc(i32 8)
  store ptr %5, ptr %7, align 8
  %8 = load ptr, ptr %a, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  %10 = load ptr, ptr %a, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load i32, ptr %11, align 4
  %13 = call %Unit @free(ptr %11)
  store i32 %12, ptr %u, align 4
  %b3 = load ptr, ptr %b, align 8
  %14 = call %Unit @printBoxInt(ptr @6, ptr %b3)
  %b4 = load ptr, ptr %b, align 8
  store i32 9, ptr %b4, align 4
  %b5 = load ptr, ptr %b, align 8
  %15 = call %Unit @printBoxInt(ptr @7, ptr %b5)
  %16 = sub nsw i32 0, 1
  %17 = call ptr @malloc(i32 4)
  store i32 %16, ptr %17, align 4
  %18 = load ptr, ptr %a, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  %20 = call ptr @malloc(i32 4)
  store i32 0, ptr %20, align 4
  %21 = load ptr, ptr %c, align 8
  %22 = call %Unit @_WriteChannel(ptr %21, ptr %20)
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

declare ptr @_address_map_has(ptr, ptr)

declare %Unit @_address_map_put(ptr, ptr, ptr)

declare %Unit @_address_map_delete(ptr)
