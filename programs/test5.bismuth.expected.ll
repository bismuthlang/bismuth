; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [12 x i8] c"CASE 1 (10)\00", align 1
@1 = private unnamed_addr constant [11 x i8] c"CASE 2 (5)\00", align 1
@2 = private unnamed_addr constant [11 x i8] c"CASE 3 (0)\00", align 1
@3 = private unnamed_addr constant [11 x i8] c"CASE 4 (a)\00", align 1
@4 = private unnamed_addr constant [12 x i8] c"f(%d) = %s\0A\00", align 1

define %Unit @nestedIf(ptr %0) {
entry:
  %a = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call ptr @_ReadLinearChannel(ptr %1)
  %3 = load i32, ptr %2, align 4
  %4 = call %Unit @free(ptr %2)
  store i32 %3, ptr %a, align 4
  %a1 = load i32, ptr %a, align 4
  %5 = icmp sgt i32 %a1, 0
  br i1 %5, label %then, label %else4

then:                                             ; preds = %entry
  %a2 = load i32, ptr %a, align 4
  %6 = icmp sgt i32 %a2, 10
  br i1 %6, label %then3, label %else

then3:                                            ; preds = %then
  %7 = call ptr @malloc(i32 8)
  store ptr @0, ptr %7, align 8
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WriteChannel(ptr %8, ptr %7)
  br label %if-cont

else:                                             ; preds = %then
  %10 = call ptr @malloc(i32 8)
  store ptr @1, ptr %10, align 8
  %11 = load ptr, ptr %c, align 8
  %12 = call %Unit @_WriteChannel(ptr %11, ptr %10)
  br label %if-cont

if-cont:                                          ; preds = %else, %then3
  br label %if-cont9

else4:                                            ; preds = %entry
  %a5 = load i32, ptr %a, align 4
  %13 = icmp eq i32 %a5, 0
  br i1 %13, label %then6, label %else7

then6:                                            ; preds = %else4
  %14 = call ptr @malloc(i32 8)
  store ptr @2, ptr %14, align 8
  %15 = load ptr, ptr %c, align 8
  %16 = call %Unit @_WriteChannel(ptr %15, ptr %14)
  br label %if-cont8

else7:                                            ; preds = %else4
  %17 = call ptr @malloc(i32 8)
  store ptr @3, ptr %17, align 8
  %18 = load ptr, ptr %c, align 8
  %19 = call %Unit @_WriteChannel(ptr %18, ptr %17)
  br label %if-cont8

if-cont8:                                         ; preds = %else7, %then6
  br label %if-cont9

if-cont9:                                         ; preds = %if-cont8, %if-cont
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %s = alloca ptr, align 8
  %io = alloca ptr, align 8
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = sub nsw i32 0, 10
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = icmp sle i32 %i1, 15
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %3 = call ptr @_Execute(ptr @nestedIf)
  store ptr %3, ptr %io, align 8
  %i2 = load i32, ptr %i, align 4
  %4 = call ptr @malloc(i32 4)
  store i32 %i2, ptr %4, align 4
  %5 = load ptr, ptr %io, align 8
  %6 = call %Unit @_WriteChannel(ptr %5, ptr %4)
  %7 = load ptr, ptr %io, align 8
  %8 = call ptr @_ReadLinearChannel(ptr %7)
  %9 = load ptr, ptr %8, align 8
  %10 = call %Unit @free(ptr %8)
  store ptr %9, ptr %s, align 8
  %i3 = load i32, ptr %i, align 4
  %s4 = load ptr, ptr %s, align 8
  %11 = call i32 (...) @printf(ptr @4, i32 %i3, ptr %s4)
  %i5 = load i32, ptr %i, align 4
  %12 = add nsw i32 %i5, 1
  store i32 %12, ptr %i, align 4
  %i6 = load i32, ptr %i, align 4
  %13 = icmp sle i32 %i6, 15
  br i1 %13, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %14 = sub nsw i32 0, 1
  %15 = call ptr @malloc(i32 4)
  store i32 %14, ptr %15, align 4
  %16 = load ptr, ptr %c, align 8
  %17 = call %Unit @_WriteChannel(ptr %16, ptr %15)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare ptr @_Execute(ptr)
