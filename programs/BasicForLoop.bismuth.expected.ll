; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [7 x i8] c"Unit, \00", align 1
@1 = private unnamed_addr constant [5 x i8] c"%i, \00", align 1
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %t = alloca i32, align 4
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %i = alloca i32, align 4
  %a = alloca [50 x i32], align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %4 = getelementptr [50 x i32], ptr %a, i32 0, i32 0
  store i32 1, ptr %4, align 4
  %5 = getelementptr [50 x i32], ptr %a, i32 0, i32 1
  store i32 2, ptr %5, align 4
  %6 = getelementptr [50 x i32], ptr %a, i32 0, i32 2
  store i32 3, ptr %6, align 4
  %7 = getelementptr [50 x i32], ptr %a, i32 0, i32 3
  store i32 4, ptr %7, align 4
  %8 = getelementptr [50 x i32], ptr %a, i32 0, i32 4
  store i32 5, ptr %8, align 4
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %9 = icmp slt i32 %i1, 10
  br i1 %9, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, ptr %i, align 4
  %10 = icmp slt i32 %i2, 50
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %11 = icmp sge i32 %i2, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr [50 x i32], ptr %a, i32 0, i32 %i2
  %13 = load i32, ptr %12, align 4
  %14 = getelementptr i32, ptr %3, i32 0, i32 0
  store i32 2, ptr %14, align 4
  %15 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store i32 %13, ptr %15, align 4
  %16 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %17 = getelementptr i32, ptr %2, i32 0, i32 0
  store i32 1, ptr %17, align 4
  %18 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %18, align 1
  %19 = load %"(Unit + int)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %16, %accessGTZ ], [ %19, %accessBad ]
  store %"(Unit + int)" %arrayAccess, ptr %1, align 4
  %20 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  %21 = load %"(Unit + int)", ptr %20, align 4
  switch %"(Unit + int)" %21, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %22 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %23 = load %Unit, ptr %22, align 1
  store %Unit %23, ptr %u, align 1
  %24 = call i32 (ptr, ...) @printf(ptr @0)
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %25 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  %26 = load i32, ptr %25, align 4
  store i32 %26, ptr %t, align 4
  %t3 = load i32, ptr %t, align 4
  %27 = call i32 (ptr, ...) @printf(ptr @1, i32 %t3)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i4 = load i32, ptr %i, align 4
  %28 = add nsw i32 %i4, 1
  store i32 %28, ptr %i, align 4
  %i5 = load i32, ptr %i, align 4
  %29 = icmp slt i32 %i5, 10
  br i1 %29, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  %30 = call i32 (ptr, ...) @printf(ptr @2)
  %31 = call ptr @malloc(i32 4)
  store i32 0, ptr %31, align 4
  %32 = load ptr, ptr %c, align 8
  %33 = call %Unit @_WriteChannel(ptr %32, ptr %31)
  ret %Unit zeroinitializer
}

declare i32 @printf(ptr, ...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
