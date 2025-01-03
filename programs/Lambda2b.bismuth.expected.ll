; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [11 x i8] c"FOO_I: %u\0A\00", align 1
@1 = private unnamed_addr constant [22 x i8] c"ref (:= foo(1)) = %u\0A\00", align 1
@2 = private unnamed_addr constant [10 x i8] c"Foo2: %u\0A\00", align 1
@3 = private unnamed_addr constant [22 x i8] c"ref (:= foo(1)) = %u\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %k.0 = alloca i32, align 4
  %j.0 = alloca i32, align 4
  %i.0 = alloca i32, align 4
  %t3.0 = alloca ptr, align 8
  %t2.0 = alloca ptr, align 8
  %t1.0 = alloca ptr, align 8
  %ref.0 = alloca ptr, align 8
  %i = alloca i32, align 4
  %t3 = alloca ptr, align 8
  %k = alloca i32, align 4
  %j = alloca i32, align 4
  %t2 = alloca ptr, align 8
  %t1 = alloca ptr, align 8
  %ref = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store ptr @"program::foo", ptr %ref, align 8
  %ref1 = load ptr, ptr %ref, align 8
  %1 = call ptr @_Execute(ptr %ref1)
  store ptr %1, ptr %t1, align 8
  %2 = call ptr @malloc(i32 4)
  store i32 10, ptr %2, align 4
  %3 = load ptr, ptr %t1, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call ptr @_Execute(ptr @"program::foo")
  store ptr %5, ptr %t2, align 8
  %6 = call ptr @malloc(i32 4)
  store i32 11, ptr %6, align 4
  %7 = load ptr, ptr %t2, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  %9 = load ptr, ptr %t1, align 8
  %10 = call ptr @_ReadLinearChannel(ptr %9)
  %11 = load i32, ptr %10, align 4
  %12 = call %Unit @free(ptr %10)
  store i32 %11, ptr %j, align 4
  %13 = load ptr, ptr %t2, align 8
  %14 = call ptr @_ReadLinearChannel(ptr %13)
  %15 = load i32, ptr %14, align 4
  %16 = call %Unit @free(ptr %14)
  store i32 %15, ptr %k, align 4
  %ref2 = load ptr, ptr %ref, align 8
  %17 = call ptr @_Execute(ptr %ref2)
  store ptr %17, ptr %t3, align 8
  %18 = call ptr @malloc(i32 4)
  store i32 1, ptr %18, align 4
  %19 = load ptr, ptr %t3, align 8
  %20 = call %Unit @_WriteChannel(ptr %19, ptr %18)
  %21 = load ptr, ptr %t3, align 8
  %22 = call ptr @_ReadLinearChannel(ptr %21)
  %23 = load i32, ptr %22, align 4
  %24 = call %Unit @free(ptr %22)
  store i32 %23, ptr %i, align 4
  %i3 = load i32, ptr %i, align 4
  %25 = call i32 (...) @printf(ptr @1, i32 %i3)
  store ptr @"program::foo.0", ptr %ref.0, align 8
  %ref.04 = load ptr, ptr %ref.0, align 8
  %26 = call ptr @_Execute(ptr %ref.04)
  store ptr %26, ptr %t1.0, align 8
  %27 = call ptr @malloc(i32 4)
  store i32 10, ptr %27, align 4
  %28 = load ptr, ptr %t1.0, align 8
  %29 = call %Unit @_WriteChannel(ptr %28, ptr %27)
  %30 = call ptr @_Execute(ptr @"program::foo.0")
  store ptr %30, ptr %t2.0, align 8
  %31 = call ptr @malloc(i32 4)
  store i32 11, ptr %31, align 4
  %32 = load ptr, ptr %t2.0, align 8
  %33 = call %Unit @_WriteChannel(ptr %32, ptr %31)
  %ref.05 = load ptr, ptr %ref.0, align 8
  %34 = call ptr @_Execute(ptr %ref.05)
  store ptr %34, ptr %t3.0, align 8
  %35 = call ptr @malloc(i32 4)
  store i32 1, ptr %35, align 4
  %36 = load ptr, ptr %t3.0, align 8
  %37 = call %Unit @_WriteChannel(ptr %36, ptr %35)
  %38 = load ptr, ptr %t3.0, align 8
  %39 = call ptr @_ReadLinearChannel(ptr %38)
  %40 = load i32, ptr %39, align 4
  %41 = call %Unit @free(ptr %39)
  store i32 %40, ptr %i.0, align 4
  %i.06 = load i32, ptr %i.0, align 4
  %42 = call i32 (...) @printf(ptr @3, i32 %i.06)
  %43 = load ptr, ptr %t1.0, align 8
  %44 = call ptr @_ReadLinearChannel(ptr %43)
  %45 = load i32, ptr %44, align 4
  %46 = call %Unit @free(ptr %44)
  store i32 %45, ptr %j.0, align 4
  %47 = load ptr, ptr %t2.0, align 8
  %48 = call ptr @_ReadLinearChannel(ptr %47)
  %49 = load i32, ptr %48, align 4
  %50 = call %Unit @free(ptr %48)
  store i32 %49, ptr %k.0, align 4
  %51 = call ptr @malloc(i32 4)
  store i32 0, ptr %51, align 4
  %52 = load ptr, ptr %c, align 8
  %53 = call %Unit @_WriteChannel(ptr %52, ptr %51)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

define private %Unit @"program::foo"(ptr %0) {
entry:
  %z = alloca i32, align 4
  %x = alloca i32, align 4
  %io = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @"program::foo::foo")
  store ptr %1, ptr %io, align 8
  %2 = load ptr, ptr %c, align 8
  %3 = call ptr @_ReadLinearChannel(ptr %2)
  %4 = load i32, ptr %3, align 4
  %5 = call %Unit @free(ptr %3)
  store i32 %4, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 %x1, ptr %6, align 4
  %7 = load ptr, ptr %io, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  %9 = load ptr, ptr %io, align 8
  %10 = call ptr @_ReadLinearChannel(ptr %9)
  %11 = load i32, ptr %10, align 4
  %12 = call %Unit @free(ptr %10)
  store i32 %11, ptr %z, align 4
  %z2 = load i32, ptr %z, align 4
  %13 = call ptr @malloc(i32 4)
  store i32 %z2, ptr %13, align 4
  %14 = load ptr, ptr %c, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  ret %Unit zeroinitializer
}

define private %Unit @"program::foo::foo"(ptr %0) {
entry:
  %x = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %x, align 4
  %x1 = load i32, ptr %x, align 4
  %5 = call i32 (...) @printf(ptr @0, i32 %x1)
  %x2 = load i32, ptr %x, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 %x2, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

define private %Unit @"program::foo.0"(ptr %0) {
entry:
  %z = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %z, align 4
  %z1 = load i32, ptr %z, align 4
  %5 = call i32 (...) @printf(ptr @2, i32 %z1)
  %z2 = load i32, ptr %z, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 %z2, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  ret %Unit zeroinitializer
}
