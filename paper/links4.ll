; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%_Channel = type opaque

@0 = private unnamed_addr constant [16 x i8] c"bool (correct)\0A\00", align 1
@1 = private unnamed_addr constant [17 x i8] c"int (incorrect)\0A\00", align 1
@2 = private unnamed_addr constant [2 x i8] c"5\00", align 1

define %Unit @foo(%_Channel* %0) {
entry:
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
  %12 = call i32 @_ReadLinearProjection(%_Channel* %11)
  switch i32 %12, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %entry
  %13 = load %_Channel*, %_Channel** %b, align 8
  %14 = call %Unit @_WriteProjection(%_Channel* %13, i32 1)
  %15 = load %_Channel*, %_Channel** %a, align 8
  %16 = call i8* @_ReadLinearChannel(%_Channel* %15)
  %17 = bitcast i8* %16 to i1*
  %18 = load i1, i1* %17, align 1
  %19 = call %Unit @free(i8* %16)
  %20 = call i8* @malloc(i32 1)
  %21 = bitcast i8* %20 to i1*
  store i1 %18, i1* %21, align 1
  %22 = load %_Channel*, %_Channel** %b, align 8
  %23 = call %Unit @_WriteChannel(%_Channel* %22, i8* %20)
  %24 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([16 x i8], [16 x i8]* @0, i32 0, i32 0))
  br label %match-cont

tagBranch2:                                       ; preds = %entry
  %25 = load %_Channel*, %_Channel** %b, align 8
  %26 = call %Unit @_WriteProjection(%_Channel* %25, i32 2)
  %27 = load %_Channel*, %_Channel** %a, align 8
  %28 = call i8* @_ReadLinearChannel(%_Channel* %27)
  %29 = bitcast i8* %28 to i32*
  %30 = load i32, i32* %29, align 4
  %31 = call %Unit @free(i8* %28)
  %32 = call i8* @malloc(i32 4)
  %33 = bitcast i8* %32 to i32*
  store i32 %30, i32* %33, align 4
  %34 = load %_Channel*, %_Channel** %b, align 8
  %35 = call %Unit @_WriteChannel(%_Channel* %34, i8* %32)
  %36 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @1, i32 0, i32 0))
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %entry
  %37 = call i8* @malloc(i32 8)
  %38 = bitcast i8* %37 to i8**
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @2, i32 0, i32 0), i8** %38, align 8
  %39 = load %_Channel*, %_Channel** %a, align 8
  %40 = call %Unit @_WriteChannel(%_Channel* %39, i8* %37)
  ret %Unit zeroinitializer
}

define %Unit @bar1(%_Channel* %0) {
entry:
  %xyz = alloca i8*, align 8
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %1 = load %_Channel*, %_Channel** %c, align 8
  %2 = call %Unit @_WriteProjection(%_Channel* %1, i32 1)
  %3 = call i8* @malloc(i32 1)
  %4 = bitcast i8* %3 to i1*
  store i1 false, i1* %4, align 1
  %5 = load %_Channel*, %_Channel** %c, align 8
  %6 = call %Unit @_WriteChannel(%_Channel* %5, i8* %3)
  %7 = load %_Channel*, %_Channel** %c, align 8
  %8 = call i8* @_ReadLinearChannel(%_Channel* %7)
  %9 = bitcast i8* %8 to i8**
  %10 = load i8*, i8** %9, align 8
  %11 = call %Unit @free(i8* %8)
  store i8* %10, i8** %xyz, align 8
  ret %Unit zeroinitializer
}

define %Unit @bar2(%_Channel* %0) {
entry:
  %i = alloca i32, align 4
  %b = alloca i1, align 1
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %1 = load %_Channel*, %_Channel** %c, align 8
  %2 = call i32 @_ReadLinearProjection(%_Channel* %1)
  switch i32 %2, label %match-cont [
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

declare i32 @_ReadLinearProjection(%_Channel*)

declare %Unit @_WriteProjection(%_Channel*, i32)

declare i8* @malloc(i32)

declare %Unit @_WriteChannel(%_Channel*, i8*)

declare %_Channel* @_Execute(%Unit (%_Channel*)*)
