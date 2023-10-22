; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%_Channel = type opaque

@0 = private unnamed_addr constant [16 x i8] c"bool (correct)\0A\00", align 1
@1 = private unnamed_addr constant [17 x i8] c"int (incorrect)\0A\00", align 1

define %Unit @linkRecvInt(%_Channel* %0, %_Channel* %1) {
entry:
  %b = alloca %_Channel*, align 8
  %a = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %a, align 8
  store %_Channel* %1, %_Channel** %b, align 8
  %2 = load %_Channel*, %_Channel** %a, align 8
  %3 = call i8* @_ReadLinearChannel(%_Channel* %2)
  %4 = bitcast i8* %3 to i32*
  %5 = load i32, i32* %4, align 4
  %6 = call %Unit @free(i8* %3)
  %7 = call i8* @malloc(i32 4)
  %8 = bitcast i8* %7 to i32*
  store i32 %5, i32* %8, align 4
  %9 = load %_Channel*, %_Channel** %b, align 8
  %10 = call %Unit @_WriteChannel(%_Channel* %9, i8* %7)
  ret %Unit zeroinitializer
}

define %Unit @linkRecvBool(%_Channel* %0, %_Channel* %1) {
entry:
  %b = alloca %_Channel*, align 8
  %a = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %a, align 8
  store %_Channel* %1, %_Channel** %b, align 8
  %2 = load %_Channel*, %_Channel** %a, align 8
  %3 = call i8* @_ReadLinearChannel(%_Channel* %2)
  %4 = bitcast i8* %3 to i1*
  %5 = load i1, i1* %4, align 1
  %6 = call %Unit @free(i8* %3)
  %7 = call i8* @malloc(i32 1)
  %8 = bitcast i8* %7 to i1*
  store i1 %5, i1* %8, align 1
  %9 = load %_Channel*, %_Channel** %b, align 8
  %10 = call %Unit @_WriteChannel(%_Channel* %9, i8* %7)
  ret %Unit zeroinitializer
}

define %Unit @foo(%_Channel* %0) {
entry:
  %i = alloca i32, align 4
  %b1 = alloca i1, align 1
  %b = alloca %_Channel*, align 8
  %a = alloca %_Channel*, align 8
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %1 = load %_Channel*, %_Channel** %c, align 8
  %2 = call i8* @_ReadLinearChannel(%_Channel* %1)
  %3 = bitcast i8* %2 to %_Channel**
  %4 = load %_Channel*, %_Channel** %3, align 8
  %5 = call %Unit @free(i8* %2)
  store %_Channel* %4, %_Channel** %a, align 8
  %6 = load %_Channel*, %_Channel** %c, align 8
  %7 = call i8* @_ReadLinearChannel(%_Channel* %6)
  %8 = bitcast i8* %7 to %_Channel**
  %9 = load %_Channel*, %_Channel** %8, align 8
  %10 = call %Unit @free(i8* %7)
  store %_Channel* %9, %_Channel** %b, align 8
  %11 = load %_Channel*, %_Channel** %a, align 8
  %12 = call %_Channel* @_ReadLinearProjection(%_Channel* %11)
  switch %_Channel* %12, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %13 = load %_Channel*, %_Channel** %a, align 8
  %14 = call i8* @_ReadLinearChannel(%_Channel* %13)
  %15 = bitcast i8* %14 to i1*
  %16 = load i1, i1* %15, align 1
  %17 = call %Unit @free(i8* %14)
  store i1 %16, i1* %b1, align 1
  %18 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @0, i32 0, i32 0))
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %19 = load %_Channel*, %_Channel** %a, align 8
  %20 = call i8* @_ReadLinearChannel(%_Channel* %19)
  %21 = bitcast i8* %20 to i32*
  %22 = load i32, i32* %21, align 4
  %23 = call %Unit @free(i8* %20)
  store i32 %22, i32* %i, align 4
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @1, i32 0, i32 0))
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %25 = load %_Channel*, %_Channel** %b, align 8
  %26 = call %Unit @_WriteProjection(%_Channel* %25, i32 2)
  %27 = call i8* @malloc(i32 4)
  %28 = bitcast i8* %27 to i32*
  store i32 0, i32* %28, align 4
  %29 = load %_Channel*, %_Channel** %b, align 8
  %30 = call %Unit @_WriteChannel(%_Channel* %29, i8* %27)
  ret %Unit zeroinitializer
}

define %Unit @bar1(%_Channel* %0) {
entry:
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %1 = load %_Channel*, %_Channel** %c, align 8
  %2 = call %Unit @_WriteProjection(%_Channel* %1, i32 1)
  %3 = call i8* @malloc(i32 1)
  %4 = bitcast i8* %3 to i1*
  store i1 false, i1* %4, align 1
  %5 = load %_Channel*, %_Channel** %c, align 8
  %6 = call %Unit @_WriteChannel(%_Channel* %5, i8* %3)
  ret %Unit zeroinitializer
}

define %Unit @bar2(%_Channel* %0) {
entry:
  %i = alloca i32, align 4
  %b = alloca i1, align 1
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %1 = load %_Channel*, %_Channel** %c, align 8
  %2 = call %_Channel* @_ReadLinearProjection(%_Channel* %1)
  switch %_Channel* %2, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %3 = load %_Channel*, %_Channel** %c, align 8
  %4 = call i8* @_ReadLinearChannel(%_Channel* %3)
  %5 = bitcast i8* %4 to i1*
  %6 = load i1, i1* %5, align 1
  %7 = call %Unit @free(i8* %4)
  store i1 %6, i1* %b, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %8 = load %_Channel*, %_Channel** %c, align 8
  %9 = call i8* @_ReadLinearChannel(%_Channel* %8)
  %10 = bitcast i8* %9 to i32*
  %11 = load i32, i32* %10, align 4
  %12 = call %Unit @free(i8* %9)
  store i32 %11, i32* %i, align 4
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  ret %Unit zeroinitializer
}

define %Unit @program(%_Channel* %0) {
entry:
  %linker = alloca %_Channel*, align 8
  %l2 = alloca %_Channel*, align 8
  %l1 = alloca %_Channel*, align 8
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %1 = call %_Channel* @_Execute(%Unit (%_Channel*)* @bar1)
  store %_Channel* %1, %_Channel** %l1, align 8
  %2 = call %_Channel* @_Execute(%Unit (%_Channel*)* @bar2)
  store %_Channel* %2, %_Channel** %l2, align 8
  %3 = call %_Channel* @_Execute(%Unit (%_Channel*)* @foo)
  store %_Channel* %3, %_Channel** %linker, align 8
  %l11 = load %_Channel*, %_Channel** %l1, align 8
  %4 = call i8* @malloc(i32 8)
  %5 = bitcast i8* %4 to %_Channel**
  store %_Channel* %l11, %_Channel** %5, align 8
  %6 = load %_Channel*, %_Channel** %linker, align 8
  %7 = call %Unit @_WriteChannel(%_Channel* %6, i8* %4)
  %l22 = load %_Channel*, %_Channel** %l2, align 8
  %8 = call i8* @malloc(i32 8)
  %9 = bitcast i8* %8 to %_Channel**
  store %_Channel* %l22, %_Channel** %9, align 8
  %10 = load %_Channel*, %_Channel** %linker, align 8
  %11 = call %Unit @_WriteChannel(%_Channel* %10, i8* %8)
  %12 = call i8* @malloc(i32 4)
  %13 = bitcast i8* %12 to i32*
  store i32 0, i32* %13, align 4
  %14 = load %_Channel*, %_Channel** %c, align 8
  %15 = call %Unit @_WriteChannel(%_Channel* %14, i8* %12)
  ret %Unit zeroinitializer
}

declare i32 @printf(i8*, ...)

declare i8* @_ReadLinearChannel(%_Channel*)

declare %Unit @free(i8*)

declare i8* @malloc(i32)

declare %Unit @_WriteChannel(%_Channel*, i8*)

declare %_Channel* @_ReadLinearProjection(i32)

declare %Unit @_WriteProjection(%_Channel*, i32)

declare %_Channel* @_Execute(%Unit (%_Channel*)*)
