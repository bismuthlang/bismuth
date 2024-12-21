; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + u32 -> Unit)" = type { i32, [8 x i8] }
%"(Unit + str)" = type { i32, [8 x i8] }
%"(Unit + u32 -> u32)" = type { i32, [8 x i8] }
%"(Unit + u32)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [6 x i8] c"Never\00", align 1
@1 = private unnamed_addr constant [5 x i8] c"Once\00", align 1
@2 = private unnamed_addr constant [6 x i8] c"Twice\00", align 1
@3 = private unnamed_addr constant [7 x i8] c"Thrice\00", align 1
@4 = private unnamed_addr constant [5 x i8] c"%uth\00", align 1
@5 = private unnamed_addr constant [11 x i8] c"IMPOSSIBLE\00", align 1
@6 = private unnamed_addr constant [6 x i8] c"Never\00", align 1
@7 = private unnamed_addr constant [5 x i8] c"Once\00", align 1
@8 = private unnamed_addr constant [6 x i8] c"Twice\00", align 1
@9 = private unnamed_addr constant [7 x i8] c"Thrice\00", align 1
@10 = private unnamed_addr constant [5 x i8] c"%uth\00", align 1
@11 = private unnamed_addr constant [11 x i8] c"IMPOSSIBLE\00", align 1
@12 = private unnamed_addr constant [6 x i8] c"Never\00", align 1
@13 = private unnamed_addr constant [5 x i8] c"Once\00", align 1
@14 = private unnamed_addr constant [6 x i8] c"Twice\00", align 1
@15 = private unnamed_addr constant [7 x i8] c"Thrice\00", align 1
@16 = private unnamed_addr constant [11 x i8] c"IMPOSSIBLE\00", align 1
@17 = private unnamed_addr constant [5 x i8] c"%uth\00", align 1
@18 = private unnamed_addr constant [15 x i8] c"Hello, World!\0A\00", align 1
@19 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

define %Unit @"programs::cursed::cursed-no-ret::more_cursed"(i32 %0) {
entry:
  %fn = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + u32 -> Unit)", align 8
  %2 = alloca %"(Unit + u32 -> Unit)", align 8
  %3 = alloca %"(Unit + u32 -> Unit)", align 8
  %arr = alloca [5 x ptr], align 8
  %4 = alloca [5 x ptr], align 8
  %r7 = alloca i32, align 4
  %r6 = alloca i32, align 4
  %r5 = alloca i32, align 4
  %r4 = alloca i32, align 4
  %r3 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %r1 = alloca i32, align 4
  %r0 = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %5 = xor i32 3, -1
  %6 = and i32 %i1, %5
  store i32 %6, ptr %r0, align 4
  %r02 = load i32, ptr %r0, align 4
  %r03 = load i32, ptr %r0, align 4
  %7 = ashr i32 %r03, 1
  %8 = or i32 %r02, %7
  store i32 %8, ptr %r1, align 4
  %r14 = load i32, ptr %r1, align 4
  %r15 = load i32, ptr %r1, align 4
  %9 = ashr i32 %r15, 2
  %10 = or i32 %r14, %9
  store i32 %10, ptr %r2, align 4
  %r26 = load i32, ptr %r2, align 4
  %r27 = load i32, ptr %r2, align 4
  %11 = ashr i32 %r27, 4
  %12 = or i32 %r26, %11
  store i32 %12, ptr %r3, align 4
  %r38 = load i32, ptr %r3, align 4
  %r39 = load i32, ptr %r3, align 4
  %13 = ashr i32 %r39, 8
  %14 = or i32 %r38, %13
  store i32 %14, ptr %r4, align 4
  %r410 = load i32, ptr %r4, align 4
  %r411 = load i32, ptr %r4, align 4
  %15 = ashr i32 %r411, 16
  %16 = or i32 %r410, %15
  store i32 %16, ptr %r5, align 4
  %r512 = load i32, ptr %r5, align 4
  %17 = and i32 %r512, 1
  %18 = shl i32 %17, 2
  store i32 %18, ptr %r6, align 4
  %r613 = load i32, ptr %r6, align 4
  %r514 = load i32, ptr %r5, align 4
  %19 = xor i32 %r514, -1
  %i15 = load i32, ptr %i, align 4
  %20 = and i32 %19, %i15
  %21 = or i32 %r613, %20
  store i32 %21, ptr %r7, align 4
  %22 = getelementptr [5 x ptr], ptr %4, i32 0, i32 0
  store ptr @"programs::cursed::cursed-no-ret::more_cursed::#lambda", ptr %22, align 8
  %23 = getelementptr [5 x ptr], ptr %4, i32 0, i32 1
  store ptr @"programs::cursed::cursed-no-ret::more_cursed::#lambda.0", ptr %23, align 8
  %24 = getelementptr [5 x ptr], ptr %4, i32 0, i32 2
  store ptr @"programs::cursed::cursed-no-ret::more_cursed::#lambda.1", ptr %24, align 8
  %25 = getelementptr [5 x ptr], ptr %4, i32 0, i32 3
  store ptr @"programs::cursed::cursed-no-ret::more_cursed::#lambda.2", ptr %25, align 8
  %26 = getelementptr [5 x ptr], ptr %4, i32 0, i32 4
  store ptr @"programs::cursed::cursed-no-ret::more_cursed::#lambda.3", ptr %26, align 8
  %27 = load [5 x ptr], ptr %4, align 8
  store [5 x ptr] %27, ptr %arr, align 8
  %r716 = load i32, ptr %r7, align 4
  %28 = icmp slt i32 %r716, 5
  br i1 %28, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %29 = icmp sge i32 %r716, 0
  br i1 %29, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %30 = getelementptr [5 x ptr], ptr %arr, i32 0, i32 %r716
  %31 = load ptr, ptr %30, align 8
  %32 = getelementptr %"(Unit + u32 -> Unit)", ptr %3, i32 0, i32 0
  store i32 2, ptr %32, align 4
  %33 = getelementptr %"(Unit + u32 -> Unit)", ptr %3, i32 0, i32 1
  store ptr %31, ptr %33, align 8
  %34 = load %"(Unit + u32 -> Unit)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %35 = getelementptr %"(Unit + u32 -> Unit)", ptr %2, i32 0, i32 0
  store i32 1, ptr %35, align 4
  %36 = getelementptr %"(Unit + u32 -> Unit)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %36, align 1
  %37 = load %"(Unit + u32 -> Unit)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32 -> Unit)" [ %34, %accessGTZ ], [ %37, %accessBad ]
  store %"(Unit + u32 -> Unit)" %arrayAccess, ptr %1, align 4
  %38 = getelementptr %"(Unit + u32 -> Unit)", ptr %1, i32 0, i32 0
  %39 = load i32, ptr %38, align 4
  switch i32 %39, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %40 = getelementptr %"(Unit + u32 -> Unit)", ptr %1, i32 0, i32 1
  %41 = load %Unit, ptr %40, align 1
  store %Unit %41, ptr %u, align 1
  %42 = call i32 (ptr, ...) @printf(ptr @5)
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %43 = getelementptr %"(Unit + u32 -> Unit)", ptr %1, i32 0, i32 1
  %44 = load ptr, ptr %43, align 8
  store ptr %44, ptr %fn, align 8
  %i17 = load i32, ptr %i, align 4
  %fn18 = load ptr, ptr %fn, align 8
  %45 = call %Unit %fn18(i32 %i17)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  ret %Unit zeroinitializer
}

define %Unit @"programs::cursed::cursed-no-ret::less_cursed"(i32 %0) {
entry:
  %fn = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + u32 -> Unit)", align 8
  %2 = alloca %"(Unit + u32 -> Unit)", align 8
  %3 = alloca %"(Unit + u32 -> Unit)", align 8
  %arr = alloca [5 x ptr], align 8
  %4 = alloca [5 x ptr], align 8
  %idx = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  store i32 %i1, ptr %idx, align 4
  %i2 = load i32, ptr %i, align 4
  %5 = icmp sgt i32 %i2, 3
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  store i32 4, ptr %idx, align 4
  br label %else

else:                                             ; preds = %then, %entry
  %6 = getelementptr [5 x ptr], ptr %4, i32 0, i32 0
  store ptr @"programs::cursed::cursed-no-ret::less_cursed::#lambda", ptr %6, align 8
  %7 = getelementptr [5 x ptr], ptr %4, i32 0, i32 1
  store ptr @"programs::cursed::cursed-no-ret::less_cursed::#lambda.0", ptr %7, align 8
  %8 = getelementptr [5 x ptr], ptr %4, i32 0, i32 2
  store ptr @"programs::cursed::cursed-no-ret::less_cursed::#lambda.1", ptr %8, align 8
  %9 = getelementptr [5 x ptr], ptr %4, i32 0, i32 3
  store ptr @"programs::cursed::cursed-no-ret::less_cursed::#lambda.2", ptr %9, align 8
  %10 = getelementptr [5 x ptr], ptr %4, i32 0, i32 4
  store ptr @"programs::cursed::cursed-no-ret::less_cursed::#lambda.3", ptr %10, align 8
  %11 = load [5 x ptr], ptr %4, align 8
  store [5 x ptr] %11, ptr %arr, align 8
  %idx3 = load i32, ptr %idx, align 4
  %12 = icmp slt i32 %idx3, 5
  br i1 %12, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %else
  %13 = icmp sge i32 %idx3, 0
  br i1 %13, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %14 = getelementptr [5 x ptr], ptr %arr, i32 0, i32 %idx3
  %15 = load ptr, ptr %14, align 8
  %16 = getelementptr %"(Unit + u32 -> Unit)", ptr %3, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + u32 -> Unit)", ptr %3, i32 0, i32 1
  store ptr %15, ptr %17, align 8
  %18 = load %"(Unit + u32 -> Unit)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %else
  %19 = getelementptr %"(Unit + u32 -> Unit)", ptr %2, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + u32 -> Unit)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + u32 -> Unit)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32 -> Unit)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  store %"(Unit + u32 -> Unit)" %arrayAccess, ptr %1, align 4
  %22 = getelementptr %"(Unit + u32 -> Unit)", ptr %1, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  switch i32 %23, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Unit + u32 -> Unit)", ptr %1, i32 0, i32 1
  %25 = load %Unit, ptr %24, align 1
  store %Unit %25, ptr %u, align 1
  %26 = call i32 (ptr, ...) @printf(ptr @11)
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %27 = getelementptr %"(Unit + u32 -> Unit)", ptr %1, i32 0, i32 1
  %28 = load ptr, ptr %27, align 8
  store ptr %28, ptr %fn, align 8
  %i4 = load i32, ptr %i, align 4
  %fn5 = load ptr, ptr %fn, align 8
  %29 = call %Unit %fn5(i32 %i4)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  ret %Unit zeroinitializer
}

define %Unit @"programs::cursed::cursed-no-ret::sel_array"(i32 %0) {
entry:
  %u = alloca %Unit, align 8
  %s = alloca ptr, align 8
  %1 = alloca %"(Unit + str)", align 8
  %2 = alloca %"(Unit + str)", align 8
  %3 = alloca %"(Unit + str)", align 8
  %arr = alloca [4 x ptr], align 8
  %4 = alloca [4 x ptr], align 8
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %5 = getelementptr [4 x ptr], ptr %4, i32 0, i32 0
  store ptr @12, ptr %5, align 8
  %6 = getelementptr [4 x ptr], ptr %4, i32 0, i32 1
  store ptr @13, ptr %6, align 8
  %7 = getelementptr [4 x ptr], ptr %4, i32 0, i32 2
  store ptr @14, ptr %7, align 8
  %8 = getelementptr [4 x ptr], ptr %4, i32 0, i32 3
  store ptr @15, ptr %8, align 8
  %9 = load [4 x ptr], ptr %4, align 8
  store [4 x ptr] %9, ptr %arr, align 8
  %i1 = load i32, ptr %i, align 4
  %10 = icmp slt i32 %i1, 4
  br i1 %10, label %then, label %else

then:                                             ; preds = %entry
  %i2 = load i32, ptr %i, align 4
  %11 = icmp slt i32 %i2, 4
  br i1 %11, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %then
  %12 = icmp sge i32 %i2, 0
  br i1 %12, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %13 = getelementptr [4 x ptr], ptr %arr, i32 0, i32 %i2
  %14 = load ptr, ptr %13, align 8
  %15 = getelementptr %"(Unit + str)", ptr %3, i32 0, i32 0
  store i32 2, ptr %15, align 4
  %16 = getelementptr %"(Unit + str)", ptr %3, i32 0, i32 1
  store ptr %14, ptr %16, align 8
  %17 = load %"(Unit + str)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %then
  %18 = getelementptr %"(Unit + str)", ptr %2, i32 0, i32 0
  store i32 1, ptr %18, align 4
  %19 = getelementptr %"(Unit + str)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %19, align 1
  %20 = load %"(Unit + str)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + str)" [ %17, %accessGTZ ], [ %20, %accessBad ]
  store %"(Unit + str)" %arrayAccess, ptr %1, align 4
  %21 = getelementptr %"(Unit + str)", ptr %1, i32 0, i32 0
  %22 = load i32, ptr %21, align 4
  switch i32 %22, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %accessAfter
  %23 = getelementptr %"(Unit + str)", ptr %1, i32 0, i32 1
  %24 = load ptr, ptr %23, align 8
  store ptr %24, ptr %s, align 8
  %s3 = load ptr, ptr %s, align 8
  %25 = call i32 (ptr, ...) @printf(ptr %s3)
  br label %match-cont

tagBranch1:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + str)", ptr %1, i32 0, i32 1
  %27 = load %Unit, ptr %26, align 1
  store %Unit %27, ptr %u, align 1
  %28 = call i32 (ptr, ...) @printf(ptr @16)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch1, %tagBranch2, %accessAfter
  br label %if-cont

else:                                             ; preds = %entry
  br i1 true, label %then4, label %if-cont

then4:                                            ; preds = %else
  %i5 = load i32, ptr %i, align 4
  %29 = call i32 (ptr, ...) @printf(ptr @17, i32 %i5)
  br label %if-cont

if-cont:                                          ; preds = %then4, %else, %match-cont
  ret %Unit zeroinitializer
}

define %Unit @program(ptr %0) {
entry:
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 (ptr, ...) @printf(ptr @18)
  %2 = call ptr @malloc(i32 4)
  store i32 0, ptr %2, align 4
  %3 = load ptr, ptr %c, align 8
  %4 = call %Unit @_WriteChannel(ptr %3, ptr %2)
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %5 = icmp slt i32 %i1, 500000
  br i1 %5, label %loop, label %rest

loop:                                             ; preds = %loop, %entry
  %i2 = load i32, ptr %i, align 4
  %6 = srem i32 %i2, 5
  %7 = call i32 @"programs::cursed::cursed-no-ret::sil_sel_each"(i32 %6)
  %i3 = load i32, ptr %i, align 4
  %8 = add nsw i32 %i3, 1
  store i32 %8, ptr %i, align 4
  %i4 = load i32, ptr %i, align 4
  %9 = icmp slt i32 %i4, 500000
  br i1 %9, label %loop, label %rest

rest:                                             ; preds = %loop, %entry
  %10 = xor i32 0, -1
  %11 = call i32 (ptr, ...) @printf(ptr @19, i32 %10)
  ret %Unit zeroinitializer
}

define i32 @"programs::cursed::cursed-no-ret::sil_more_cursed"(i32 %0) {
entry:
  %fn = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + u32 -> u32)", align 8
  %2 = alloca %"(Unit + u32 -> u32)", align 8
  %3 = alloca %"(Unit + u32 -> u32)", align 8
  %arr = alloca [5 x ptr], align 8
  %4 = alloca [5 x ptr], align 8
  %r7 = alloca i32, align 4
  %r6 = alloca i32, align 4
  %r5 = alloca i32, align 4
  %r4 = alloca i32, align 4
  %r3 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %r1 = alloca i32, align 4
  %r0 = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %5 = xor i32 3, -1
  %6 = and i32 %i1, %5
  store i32 %6, ptr %r0, align 4
  %r02 = load i32, ptr %r0, align 4
  %r03 = load i32, ptr %r0, align 4
  %7 = ashr i32 %r03, 1
  %8 = or i32 %r02, %7
  store i32 %8, ptr %r1, align 4
  %r14 = load i32, ptr %r1, align 4
  %r15 = load i32, ptr %r1, align 4
  %9 = ashr i32 %r15, 2
  %10 = or i32 %r14, %9
  store i32 %10, ptr %r2, align 4
  %r26 = load i32, ptr %r2, align 4
  %r27 = load i32, ptr %r2, align 4
  %11 = ashr i32 %r27, 4
  %12 = or i32 %r26, %11
  store i32 %12, ptr %r3, align 4
  %r38 = load i32, ptr %r3, align 4
  %r39 = load i32, ptr %r3, align 4
  %13 = ashr i32 %r39, 8
  %14 = or i32 %r38, %13
  store i32 %14, ptr %r4, align 4
  %r410 = load i32, ptr %r4, align 4
  %r411 = load i32, ptr %r4, align 4
  %15 = ashr i32 %r411, 16
  %16 = or i32 %r410, %15
  store i32 %16, ptr %r5, align 4
  %r512 = load i32, ptr %r5, align 4
  %17 = and i32 %r512, 1
  %18 = shl i32 %17, 2
  store i32 %18, ptr %r6, align 4
  %r613 = load i32, ptr %r6, align 4
  %r514 = load i32, ptr %r5, align 4
  %19 = xor i32 %r514, -1
  %i15 = load i32, ptr %i, align 4
  %20 = and i32 %19, %i15
  %21 = or i32 %r613, %20
  store i32 %21, ptr %r7, align 4
  %22 = getelementptr [5 x ptr], ptr %4, i32 0, i32 0
  store ptr @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda", ptr %22, align 8
  %23 = getelementptr [5 x ptr], ptr %4, i32 0, i32 1
  store ptr @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.0", ptr %23, align 8
  %24 = getelementptr [5 x ptr], ptr %4, i32 0, i32 2
  store ptr @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.1", ptr %24, align 8
  %25 = getelementptr [5 x ptr], ptr %4, i32 0, i32 3
  store ptr @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.2", ptr %25, align 8
  %26 = getelementptr [5 x ptr], ptr %4, i32 0, i32 4
  store ptr @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.3", ptr %26, align 8
  %27 = load [5 x ptr], ptr %4, align 8
  store [5 x ptr] %27, ptr %arr, align 8
  %r716 = load i32, ptr %r7, align 4
  %28 = icmp slt i32 %r716, 5
  br i1 %28, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %29 = icmp sge i32 %r716, 0
  br i1 %29, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %30 = getelementptr [5 x ptr], ptr %arr, i32 0, i32 %r716
  %31 = load ptr, ptr %30, align 8
  %32 = getelementptr %"(Unit + u32 -> u32)", ptr %3, i32 0, i32 0
  store i32 2, ptr %32, align 4
  %33 = getelementptr %"(Unit + u32 -> u32)", ptr %3, i32 0, i32 1
  store ptr %31, ptr %33, align 8
  %34 = load %"(Unit + u32 -> u32)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %35 = getelementptr %"(Unit + u32 -> u32)", ptr %2, i32 0, i32 0
  store i32 1, ptr %35, align 4
  %36 = getelementptr %"(Unit + u32 -> u32)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %36, align 1
  %37 = load %"(Unit + u32 -> u32)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32 -> u32)" [ %34, %accessGTZ ], [ %37, %accessBad ]
  store %"(Unit + u32 -> u32)" %arrayAccess, ptr %1, align 4
  %38 = getelementptr %"(Unit + u32 -> u32)", ptr %1, i32 0, i32 0
  %39 = load i32, ptr %38, align 4
  switch i32 %39, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %40 = getelementptr %"(Unit + u32 -> u32)", ptr %1, i32 0, i32 1
  %41 = load %Unit, ptr %40, align 1
  store %Unit %41, ptr %u, align 1
  %42 = sub nsw i32 0, 1
  ret i32 %42

tagBranch2:                                       ; preds = %accessAfter
  %43 = getelementptr %"(Unit + u32 -> u32)", ptr %1, i32 0, i32 1
  %44 = load ptr, ptr %43, align 8
  store ptr %44, ptr %fn, align 8
  %i17 = load i32, ptr %i, align 4
  %fn18 = load ptr, ptr %fn, align 8
  %45 = call i32 %fn18(i32 %i17)
  ret i32 %45

match-cont:                                       ; preds = %accessAfter
  unreachable
}

define i32 @"programs::cursed::cursed-no-ret::sil_less_cursed"(i32 %0) {
entry:
  %fn = alloca ptr, align 8
  %u = alloca %Unit, align 8
  %1 = alloca %"(Unit + u32 -> u32)", align 8
  %2 = alloca %"(Unit + u32 -> u32)", align 8
  %3 = alloca %"(Unit + u32 -> u32)", align 8
  %arr = alloca [5 x ptr], align 8
  %4 = alloca [5 x ptr], align 8
  %idx = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  store i32 %i1, ptr %idx, align 4
  %i2 = load i32, ptr %i, align 4
  %5 = icmp sgt i32 %i2, 3
  br i1 %5, label %then, label %else

then:                                             ; preds = %entry
  store i32 4, ptr %idx, align 4
  br label %else

else:                                             ; preds = %then, %entry
  %6 = getelementptr [5 x ptr], ptr %4, i32 0, i32 0
  store ptr @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda", ptr %6, align 8
  %7 = getelementptr [5 x ptr], ptr %4, i32 0, i32 1
  store ptr @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.0", ptr %7, align 8
  %8 = getelementptr [5 x ptr], ptr %4, i32 0, i32 2
  store ptr @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.1", ptr %8, align 8
  %9 = getelementptr [5 x ptr], ptr %4, i32 0, i32 3
  store ptr @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.2", ptr %9, align 8
  %10 = getelementptr [5 x ptr], ptr %4, i32 0, i32 4
  store ptr @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.3", ptr %10, align 8
  %11 = load [5 x ptr], ptr %4, align 8
  store [5 x ptr] %11, ptr %arr, align 8
  %idx3 = load i32, ptr %idx, align 4
  %12 = icmp slt i32 %idx3, 5
  br i1 %12, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %else
  %13 = icmp sge i32 %idx3, 0
  br i1 %13, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %14 = getelementptr [5 x ptr], ptr %arr, i32 0, i32 %idx3
  %15 = load ptr, ptr %14, align 8
  %16 = getelementptr %"(Unit + u32 -> u32)", ptr %3, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + u32 -> u32)", ptr %3, i32 0, i32 1
  store ptr %15, ptr %17, align 8
  %18 = load %"(Unit + u32 -> u32)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %else
  %19 = getelementptr %"(Unit + u32 -> u32)", ptr %2, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + u32 -> u32)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + u32 -> u32)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32 -> u32)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  store %"(Unit + u32 -> u32)" %arrayAccess, ptr %1, align 4
  %22 = getelementptr %"(Unit + u32 -> u32)", ptr %1, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  switch i32 %23, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Unit + u32 -> u32)", ptr %1, i32 0, i32 1
  %25 = load %Unit, ptr %24, align 1
  store %Unit %25, ptr %u, align 1
  %26 = sub nsw i32 0, 1
  ret i32 %26

tagBranch2:                                       ; preds = %accessAfter
  %27 = getelementptr %"(Unit + u32 -> u32)", ptr %1, i32 0, i32 1
  %28 = load ptr, ptr %27, align 8
  store ptr %28, ptr %fn, align 8
  %i4 = load i32, ptr %i, align 4
  %fn5 = load ptr, ptr %fn, align 8
  %29 = call i32 %fn5(i32 %i4)
  ret i32 %29

match-cont:                                       ; preds = %accessAfter
  unreachable
}

define i32 @"programs::cursed::cursed-no-ret::sil_sel_array"(i32 %0) {
entry:
  %u = alloca %Unit, align 8
  %s = alloca i32, align 4
  %1 = alloca %"(Unit + u32)", align 8
  %2 = alloca %"(Unit + u32)", align 8
  %3 = alloca %"(Unit + u32)", align 8
  %arr = alloca [4 x i32], align 4
  %4 = alloca [4 x i32], align 4
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %5 = getelementptr [4 x i32], ptr %4, i32 0, i32 0
  store i32 0, ptr %5, align 4
  %6 = getelementptr [4 x i32], ptr %4, i32 0, i32 1
  store i32 1, ptr %6, align 4
  %7 = getelementptr [4 x i32], ptr %4, i32 0, i32 2
  store i32 2, ptr %7, align 4
  %8 = getelementptr [4 x i32], ptr %4, i32 0, i32 3
  store i32 3, ptr %8, align 4
  %9 = load [4 x i32], ptr %4, align 4
  store [4 x i32] %9, ptr %arr, align 4
  %i1 = load i32, ptr %i, align 4
  %10 = icmp slt i32 %i1, 4
  br i1 %10, label %then, label %else

then:                                             ; preds = %entry
  %i2 = load i32, ptr %i, align 4
  %11 = icmp slt i32 %i2, 4
  br i1 %11, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %then
  %12 = icmp sge i32 %i2, 0
  br i1 %12, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %13 = getelementptr [4 x i32], ptr %arr, i32 0, i32 %i2
  %14 = load i32, ptr %13, align 4
  %15 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 0
  store i32 2, ptr %15, align 4
  %16 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 1
  store i32 %14, ptr %16, align 4
  %17 = load %"(Unit + u32)", ptr %3, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %then
  %18 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 0
  store i32 1, ptr %18, align 4
  %19 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 1
  store %Unit zeroinitializer, ptr %19, align 1
  %20 = load %"(Unit + u32)", ptr %2, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32)" [ %17, %accessGTZ ], [ %20, %accessBad ]
  store %"(Unit + u32)" %arrayAccess, ptr %1, align 4
  %21 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 0
  %22 = load i32, ptr %21, align 4
  switch i32 %22, label %match-cont [
    i32 2, label %tagBranch2
    i32 1, label %tagBranch1
  ]

tagBranch2:                                       ; preds = %accessAfter
  %23 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 1
  %24 = load i32, ptr %23, align 4
  store i32 %24, ptr %s, align 4
  %s3 = load i32, ptr %s, align 4
  ret i32 %s3

tagBranch1:                                       ; preds = %accessAfter
  %25 = getelementptr %"(Unit + u32)", ptr %1, i32 0, i32 1
  %26 = load %Unit, ptr %25, align 1
  store %Unit %26, ptr %u, align 1
  %27 = sub nsw i32 0, 1
  ret i32 %27

match-cont:                                       ; preds = %accessAfter
  br label %if-cont

else:                                             ; preds = %entry
  br i1 true, label %then4, label %if-cont

then4:                                            ; preds = %else
  %i5 = load i32, ptr %i, align 4
  ret i32 %i5

if-cont:                                          ; preds = %else, %match-cont
  unreachable
}

define i32 @"programs::cursed::cursed-no-ret::sil_sel_each"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = icmp eq i32 %i1, 0
  br i1 %1, label %then, label %else

then:                                             ; preds = %entry
  ret i32 0

else:                                             ; preds = %entry
  %i2 = load i32, ptr %i, align 4
  %2 = icmp eq i32 %i2, 1
  br i1 %2, label %then3, label %else4

then3:                                            ; preds = %else
  ret i32 1

else4:                                            ; preds = %else
  %i5 = load i32, ptr %i, align 4
  %3 = icmp eq i32 %i5, 2
  br i1 %3, label %then6, label %else7

then6:                                            ; preds = %else4
  ret i32 2

else7:                                            ; preds = %else4
  %i8 = load i32, ptr %i, align 4
  %4 = icmp eq i32 %i8, 3
  br i1 %4, label %then9, label %else10

then9:                                            ; preds = %else7
  ret i32 3

else10:                                           ; preds = %else7
  br i1 true, label %then11, label %if-cont

then11:                                           ; preds = %else10
  %i12 = load i32, ptr %i, align 4
  ret i32 %i12

if-cont:                                          ; preds = %else10
  unreachable
}

declare i32 @printf(ptr, ...)

define private %Unit @"programs::cursed::cursed-no-ret::more_cursed::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @0)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::more_cursed::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @1)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::more_cursed::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @2)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::more_cursed::#lambda.2"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @3)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::more_cursed::#lambda.3"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @4, i32 %i1)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::less_cursed::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @6)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::less_cursed::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @7)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::less_cursed::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @8)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::less_cursed::#lambda.2"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @9)
  ret %Unit zeroinitializer
}

define private %Unit @"programs::cursed::cursed-no-ret::less_cursed::#lambda.3"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call i32 (ptr, ...) @printf(ptr @10, i32 %i1)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

define private i32 @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 0
}

define private i32 @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 1
}

define private i32 @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 2
}

define private i32 @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.2"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 3
}

define private i32 @"programs::cursed::cursed-no-ret::sil_more_cursed::#lambda.3"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}

define private i32 @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 0
}

define private i32 @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 1
}

define private i32 @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 2
}

define private i32 @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.2"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  ret i32 3
}

define private i32 @"programs::cursed::cursed-no-ret::sil_less_cursed::#lambda.3"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}
