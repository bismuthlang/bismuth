; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [13 x i8] c"Sending! %u\0A\00", align 1
@1 = private unnamed_addr constant [252 x i8] c"Well hello there. This is a very long string. And I hope it will take up a lot of memory. Just so that way we can prove how we are in fact clearing memory over time---hopefully. Lets see what happens! This will be fun! (lol it wont be). But who cares?\00", align 1

define %Unit @sender(ptr %0) {
entry:
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  store i32 0, ptr %i, align 4
  br i1 true, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %1 = load ptr, ptr %c, align 8
  %2 = call %Unit @_ContractChannel(ptr %1)
  %i1 = load i32, ptr %i, align 4
  %3 = call i32 (ptr, ...) @printf(ptr @0, i32 %i1)
  %i2 = load i32, ptr %i, align 4
  %4 = add nsw i32 %i2, 1
  store i32 %4, ptr %i, align 4
  %5 = call ptr @malloc(i32 8)
  store ptr @1, ptr %5, align 8
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  br i1 true, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %8 = load ptr, ptr %c, align 8
  %9 = call %Unit @_WeakenChannel(ptr %8)
  ret %Unit zeroinitializer
}

define %Unit @reciever(ptr %0) {
entry:
  %s = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = load ptr, ptr %c, align 8
  %2 = call i1 @_ShouldLinearLoop(ptr %1)
  br i1 %2, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %3 = load ptr, ptr %c, align 8
  %4 = call ptr @_ReadLinearChannel(ptr %3)
  %5 = load ptr, ptr %4, align 8
  %6 = call %Unit @free(ptr %4)
  store ptr %5, ptr %s, align 8
  %7 = load ptr, ptr %c, align 8
  %8 = call i1 @_ShouldLinearLoop(ptr %7)
  br i1 %8, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %i = alloca ptr, align 8
  %b = alloca ptr, align 8
  %a = alloca ptr, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call ptr @_Execute(ptr @sender)
  store ptr %1, ptr %a, align 8
  %2 = call ptr @_Execute(ptr @reciever)
  store ptr %2, ptr %b, align 8
  %3 = load ptr, ptr %a, align 8
  %4 = call i1 @_ShouldLinearLoop(ptr %3)
  br i1 %4, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %5 = load ptr, ptr %a, align 8
  %6 = call ptr @_ReadLinearChannel(ptr %5)
  %7 = load ptr, ptr %6, align 8
  %8 = call %Unit @free(ptr %6)
  store ptr %7, ptr %i, align 8
  %9 = load ptr, ptr %a, align 8
  %10 = call i1 @_ShouldLinearLoop(ptr %9)
  br i1 %10, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %11 = load ptr, ptr %b, align 8
  %12 = call %Unit @_WeakenChannel(ptr %11)
  %13 = call ptr @malloc(i32 4)
  store i32 0, ptr %13, align 4
  %14 = load ptr, ptr %c, align 8
  %15 = call %Unit @_WriteChannel(ptr %14, ptr %13)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare %Unit @_ContractChannel(ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

declare %Unit @_WeakenChannel(ptr)

declare i1 @_ShouldLinearLoop(ptr)

declare ptr @_ReadLinearChannel(ptr)

declare %Unit @free(ptr)

declare ptr @_Execute(ptr)
