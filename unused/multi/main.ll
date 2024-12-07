; ModuleID = 'WPLC.ll'
source_filename = "WPLC.ll"

@0 = private unnamed_addr constant [31 x i8] c"Needs at least two arguments!\0A\00", align 1
@1 = private unnamed_addr constant [25 x i8] c"Got strings: {%s}, {%s}\0A\00", align 1
@2 = private unnamed_addr constant [13 x i8] c"%d^%d = %d\0A\0A\00", align 1

declare i32 @printf(i8*, ...)

declare i32 @getArgCount()

declare i8* @getStrArg(i32)

declare i32 @getIntArg(i32)

declare i32 @pow(i32, i32)

define i32 @program() {
entry:
  %0 = call i32 @getArgCount()
  %1 = icmp slt i32 %0, 2
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  %2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @0, i32 0, i32 0))
  %3 = sub nsw i32 0, 1
  ret i32 %3

else:                                             ; preds = %entry
  %i = alloca i32, align 4
  store i32 1, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %4 = add nsw i32 %i1, 1
  %5 = call i32 @getArgCount()
  %6 = icmp slt i32 %4, %5
  br i1 %6, label %loop, label %rest

loop:                                             ; preds = %loop, %else
  %i2 = load i32, i32* %i, align 4
  %7 = call i8* @getStrArg(i32 %i2)
  %a_str = alloca i8*, align 8
  store i8* %7, i8** %a_str, align 8
  %i3 = load i32, i32* %i, align 4
  %8 = add nsw i32 %i3, 1
  %9 = call i8* @getStrArg(i32 %8)
  %b_str = alloca i8*, align 8
  store i8* %9, i8** %b_str, align 8
  %i4 = load i32, i32* %i, align 4
  %10 = call i32 @getIntArg(i32 %i4)
  %a_int = alloca i32, align 4
  store i32 %10, i32* %a_int, align 4
  %i5 = load i32, i32* %i, align 4
  %11 = add nsw i32 %i5, 1
  %12 = call i32 @getIntArg(i32 %11)
  %b_int = alloca i32, align 4
  store i32 %12, i32* %b_int, align 4
  %a_str6 = load i8*, i8** %a_str, align 8
  %b_str7 = load i8*, i8** %b_str, align 8
  %13 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([25 x i8], [25 x i8]* @1, i32 0, i32 0), i8* %a_str6, i8* %b_str7)
  %a_int8 = load i32, i32* %a_int, align 4
  %b_int9 = load i32, i32* %b_int, align 4
  %14 = call i32 @pow(i32 %a_int8, i32 %b_int9)
  %ans = alloca i32, align 4
  store i32 %14, i32* %ans, align 4
  %a_int10 = load i32, i32* %a_int, align 4
  %b_int11 = load i32, i32* %b_int, align 4
  %ans12 = load i32, i32* %ans, align 4
  %15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @2, i32 0, i32 0), i32 %a_int10, i32 %b_int11, i32 %ans12)
  %i13 = load i32, i32* %i, align 4
  %16 = add nsw i32 %i13, 1
  store i32 %16, i32* %i, align 4
  %i14 = load i32, i32* %i, align 4
  %17 = add nsw i32 %i14, 1
  %18 = call i32 @getArgCount()
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %loop, label %rest

rest:                                             ; preds = %loop, %else
  ret i32 0
}
