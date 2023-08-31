; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [16 x i8] c"bool (correct)\0A\00", align 1
@1 = private unnamed_addr constant [17 x i8] c"int (incorrect)\0A\00", align 1

define %Unit @linkRecvInt(i32 %0, i32 %1) {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  store i32 %1, i32* %b, align 4
  %2 = load i32, i32* %a, align 4
  %3 = call i8* @ReadChannel(i32 %2)
  %4 = bitcast i8* %3 to i32*
  %5 = load i32, i32* %4, align 4
  %6 = call %Unit @free(i8* %3)
  %7 = call i8* @malloc(i32 4)
  %8 = bitcast i8* %7 to i32*
  store i32 %5, i32* %8, align 4
  %9 = load i32, i32* %b, align 4
  %10 = call %Unit @WriteChannel(i32 %9, i8* %7)
  ret %Unit zeroinitializer
}

define %Unit @linkRecvBool(i32 %0, i32 %1) {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  store i32 %1, i32* %b, align 4
  %2 = load i32, i32* %a, align 4
  %3 = call i8* @ReadChannel(i32 %2)
  %4 = bitcast i8* %3 to i1*
  %5 = load i1, i1* %4, align 1
  %6 = call %Unit @free(i8* %3)
  %7 = call i8* @malloc(i32 1)
  %8 = bitcast i8* %7 to i1*
  store i1 %5, i1* %8, align 1
  %9 = load i32, i32* %b, align 4
  %10 = call %Unit @WriteChannel(i32 %9, i8* %7)
  ret %Unit zeroinitializer
}

define %Unit @foo(i32 %0) {
entry:
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  %2 = call i8* @ReadChannel(i32 %1)
  %3 = bitcast i8* %2 to i32*
  %4 = load i32, i32* %3, align 4
  %5 = call %Unit @free(i8* %2)
  store i32 %4, i32* %a, align 4
  %6 = load i32, i32* %c, align 4
  %7 = call i8* @ReadChannel(i32 %6)
  %8 = bitcast i8* %7 to i32*
  %9 = load i32, i32* %8, align 4
  %10 = call %Unit @free(i8* %7)
  store i32 %9, i32* %b, align 4
  %11 = load i32, i32* %a, align 4
  %12 = call i32 @ReadProjection(i32 %11)
  switch i32 %12, label %matchcont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %13 = load i32, i32* %b, align 4
  %14 = call %Unit @WriteProjection(i32 %13, i32 1)
  %a1 = load i32, i32* %a, align 4
  %b2 = load i32, i32* %b, align 4
  %15 = call %Unit @linkRecvBool(i32 %a1, i32 %b2)
  %16 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @0, i32 0, i32 0))
  br label %matchcont

tagBranch2:                                       ; preds = %entry
  %17 = load i32, i32* %b, align 4
  %18 = call %Unit @WriteProjection(i32 %17, i32 2)
  %a3 = load i32, i32* %a, align 4
  %b4 = load i32, i32* %b, align 4
  %19 = call %Unit @linkRecvInt(i32 %a3, i32 %b4)
  %20 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @1, i32 0, i32 0))
  br label %matchcont

matchcont:                                        ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @bar1(i32 %0) {
entry:
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  %2 = call %Unit @WriteProjection(i32 %1, i32 1)
  %3 = call i8* @malloc(i32 1)
  %4 = bitcast i8* %3 to i1*
  store i1 false, i1* %4, align 1
  %5 = load i32, i32* %c, align 4
  %6 = call %Unit @WriteChannel(i32 %5, i8* %3)
  ret %Unit zeroinitializer
}

define %Unit @bar2(i32 %0) {
entry:
  %i = alloca i32, align 4
  %b = alloca i1, align 1
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32, i32* %c, align 4
  %2 = call i32 @ReadProjection(i32 %1)
  switch i32 %2, label %matchcont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %3 = load i32, i32* %c, align 4
  %4 = call i8* @ReadChannel(i32 %3)
  %5 = bitcast i8* %4 to i1*
  %6 = load i1, i1* %5, align 1
  %7 = call %Unit @free(i8* %4)
  store i1 %6, i1* %b, align 1
  br label %matchcont

tagBranch2:                                       ; preds = %entry
  %8 = load i32, i32* %c, align 4
  %9 = call i8* @ReadChannel(i32 %8)
  %10 = bitcast i8* %9 to i32*
  %11 = load i32, i32* %10, align 4
  %12 = call %Unit @free(i8* %9)
  store i32 %11, i32* %i, align 4
  br label %matchcont

matchcont:                                        ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(i32 %0) {
entry:
  %linker = alloca i32, align 4
  %l2 = alloca i32, align 4
  %l1 = alloca i32, align 4
  %c = alloca i32, align 4
  store i32 %0, i32* %c, align 4
  %1 = call i32 @Execute(%Unit (i32)* @bar1)
  store i32 %1, i32* %l1, align 4
  %2 = call i32 @Execute(%Unit (i32)* @bar2)
  store i32 %2, i32* %l2, align 4
  %3 = call i32 @Execute(%Unit (i32)* @foo)
  store i32 %3, i32* %linker, align 4
  %l11 = load i32, i32* %l1, align 4
  %4 = call i8* @malloc(i32 4)
  %5 = bitcast i8* %4 to i32*
  store i32 %l11, i32* %5, align 4
  %6 = load i32, i32* %linker, align 4
  %7 = call %Unit @WriteChannel(i32 %6, i8* %4)
  %l22 = load i32, i32* %l2, align 4
  %8 = call i8* @malloc(i32 4)
  %9 = bitcast i8* %8 to i32*
  store i32 %l22, i32* %9, align 4
  %10 = load i32, i32* %linker, align 4
  %11 = call %Unit @WriteChannel(i32 %10, i8* %8)
  %12 = call i8* @malloc(i32 4)
  %13 = bitcast i8* %12 to i32*
  store i32 0, i32* %13, align 4
  %14 = load i32, i32* %c, align 4
  %15 = call %Unit @WriteChannel(i32 %14, i8* %12)
  ret %Unit zeroinitializer
}

declare i32 @printf(i8*, ...)

declare i8* @ReadChannel(i32)

declare %Unit @free(i8*)

declare i8* @malloc(i32)

declare %Unit @WriteChannel(i32, i8*)

declare i32 @ReadProjection(i32)

declare %Unit @WriteProjection(i32, i32)

declare i32 @Execute(%Unit (i32)*)
