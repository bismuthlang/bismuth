; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [5 x i8] c"why\0A\00", align 1
@1 = private unnamed_addr constant [6 x i8] c"why2\0A\00", align 1
@2 = private unnamed_addr constant [6 x i8] c"why3\0A\00", align 1
@3 = private unnamed_addr constant [6 x i8] c"why4\0A\00", align 1
@4 = private unnamed_addr constant [6 x i8] c"wh52\0A\00", align 1
@5 = private unnamed_addr constant [9 x i8] c"Got: %u\0A\00", align 1
@6 = private unnamed_addr constant [6 x i8] c"z=%u\0A\00", align 1
@7 = private unnamed_addr constant [20 x i8] c"And the other one!\0A\00", align 1
@8 = private unnamed_addr constant [25 x i8] c"And the other one SENT!\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %z = alloca i32, align 4
  %c3 = alloca ptr, align 8
  %y = alloca i32, align 4
  %c2 = alloca ptr, align 8
  %current = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 (ptr, ...) @printf(ptr @0)
  %2 = call i32 @getArgCount()
  store i32 20, ptr %current, align 4
  %3 = call i32 (ptr, ...) @printf(ptr @1)
  %current1 = load i32, ptr %current, align 4
  %4 = call ptr @malloc(i32 4)
  store i32 %current1, ptr %4, align 4
  %5 = load ptr, ptr %c, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  %7 = call i32 (ptr, ...) @printf(ptr @2)
  %8 = call ptr @_Execute(ptr @simple)
  store ptr %8, ptr %c2, align 8
  %9 = call i32 (ptr, ...) @printf(ptr @3)
  %10 = load ptr, ptr %c2, align 8
  %11 = call ptr @_ReadLinearChannel(ptr %10)
  %12 = load i32, ptr %11, align 4
  %13 = call %Unit @free(ptr %11)
  store i32 %12, ptr %y, align 4
  %14 = call i32 (ptr, ...) @printf(ptr @4)
  %y2 = load i32, ptr %y, align 4
  %15 = call i32 (ptr, ...) @printf(ptr @5, i32 %y2)
  %16 = call ptr @_Execute(ptr @bar)
  store ptr %16, ptr %c3, align 8
  %17 = load ptr, ptr %c3, align 8
  %18 = call i1 @_ShouldLinearLoop(ptr %17)
  br i1 %18, label %loop, label %rest5

loop:                                             ; preds = %rest, %entry
  %19 = load ptr, ptr %c3, align 8
  %20 = call i1 @_ShouldLinearLoop(ptr %19)
  br i1 %20, label %loop3, label %rest

loop3:                                            ; preds = %loop3, %loop
  %21 = load ptr, ptr %c3, align 8
  %22 = call ptr @_ReadLinearChannel(ptr %21)
  %23 = load i32, ptr %22, align 4
  %24 = call %Unit @free(ptr %22)
  store i32 %23, ptr %z, align 4
  %z4 = load i32, ptr %z, align 4
  %25 = call i32 (ptr, ...) @printf(ptr @6, i32 %z4)
  %26 = load ptr, ptr %c3, align 8
  %27 = call i1 @_ShouldLinearLoop(ptr %26)
  br i1 %27, label %loop3, label %rest

rest:                                             ; preds = %loop3, %loop
  %28 = load ptr, ptr %c3, align 8
  %29 = call i1 @_ShouldLinearLoop(ptr %28)
  br i1 %29, label %loop, label %rest5

rest5:                                            ; preds = %rest, %entry
  %30 = call ptr @malloc(i32 4)
  store i32 7, ptr %30, align 4
  %31 = load ptr, ptr %c3, align 8
  %32 = call %Unit @_WriteChannel(ptr %31, ptr %30)
  ret %Unit zeroinitializer
}

define %Unit @simple(ptr %0) {
entry:
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 (ptr, ...) @printf(ptr @7)
  %2 = call ptr @malloc(i32 4)
  store i32 5, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  %5 = call i32 (ptr, ...) @printf(ptr @8)
  ret %Unit zeroinitializer
}

define %Unit @bar(ptr %0) {
entry:
  %a = alloca i32, align 4
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = icmp slt i32 %i1, 5
  br i1 %1, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %2 = load ptr, ptr %c, align 8
  %3 = call %Unit @_ContractChannel(ptr %2)
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_ContractChannel(ptr %4)
  %i2 = load i32, ptr %i, align 4
  %6 = call ptr @malloc(i32 4)
  store i32 %i2, ptr %6, align 4
  %7 = load ptr, ptr %c, align 8
  %8 = call %Unit @_WriteChannel(ptr %7, ptr %6)
  %9 = load ptr, ptr %c, align 8
  %10 = call %Unit @_WeakenChannel(ptr %9)
  %i3 = load i32, ptr %i, align 4
  %11 = add nsw i32 %i3, 1
  store i32 %11, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %12 = icmp slt i32 %i4, 5
  br i1 %12, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %13 = load ptr, ptr %c, align 8
  %14 = call %Unit @_WeakenChannel(ptr %13)
  %15 = load ptr, ptr %c, align 8
  %16 = call ptr @_ReadLinearChannel(ptr %15)
  %17 = load i32, ptr %16, align 4
  %18 = call %Unit @free(ptr %16)
  store i32 %17, ptr %a, align 4
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare i32 @getArgCount()

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare i1 @_ShouldLinearLoop(ptr)

declare %Unit @_ContractChannel(ptr)

declare %Unit @_WeakenChannel(ptr)
