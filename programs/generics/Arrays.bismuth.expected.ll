; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"u32[]" = type { ptr, i32, i32 }
%"(u32 -> u32 + u32, u32 -> u32)" = type { i32, [8 x i8] }
%"boolean[]" = type { ptr, i32, i32 }
%"(Unit + u32)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [10 x i8] c"Size: %u\0A\00", align 1
@1 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@2 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@3 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %a24 = alloca %"u32[]", align 8
  %1 = alloca %"(u32 -> u32 + u32, u32 -> u32)", align 8
  %d = alloca ptr, align 8
  %fillBools = alloca ptr, align 8
  %b = alloca %"boolean[]", align 8
  %a = alloca %"u32[]", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = getelementptr %"u32[]", ptr %a, i32 0, i32 0
  %3 = sext i32 2 to i64
  %4 = mul nsw i64 %3, 4
  %5 = call ptr @GC_malloc(i64 %4)
  store ptr %5, ptr %2, align 8
  %6 = getelementptr %"u32[]", ptr %a, i32 0, i32 1
  store i32 1, ptr %6, align 4
  %7 = getelementptr %"u32[]", ptr %a, i32 0, i32 2
  store i32 2, ptr %7, align 4
  %8 = getelementptr %"boolean[]", ptr %b, i32 0, i32 0
  %9 = sext i32 2 to i64
  %10 = mul nsw i64 %9, 1
  %11 = call ptr @GC_malloc(i64 %10)
  store ptr %11, ptr %8, align 8
  %12 = getelementptr %"boolean[]", ptr %b, i32 0, i32 1
  store i32 1, ptr %12, align 4
  %13 = getelementptr %"boolean[]", ptr %b, i32 0, i32 2
  store i32 2, ptr %13, align 4
  store ptr @"fill<u32>", ptr %d, align 8
  %a1 = load %"u32[]", ptr %a, align 8
  %14 = call %Unit @"fill<u32>"(%"u32[]" %a1, i32 2, i32 5)
  %15 = getelementptr %"u32[]", ptr %a, i32 0, i32 1
  %16 = load i32, ptr %15, align 4
  %17 = call %Unit (ptr, ...) @printf(ptr @0, i32 %16)
  %a2 = load %"u32[]", ptr %a, align 8
  %18 = call %Unit @"forEach<u32>"(%"u32[]" %a2, ptr @"program::#lambda")
  %19 = call %Unit (ptr, ...) @printf(ptr @2)
  %a3 = load %"u32[]", ptr %a, align 8
  %20 = getelementptr %"(u32 -> u32 + u32, u32 -> u32)", ptr %1, i32 0, i32 0
  store i32 2, ptr %20, align 4
  %21 = getelementptr %"(u32 -> u32 + u32, u32 -> u32)", ptr %1, i32 0, i32 1
  store ptr @"program::#lambda.0", ptr %21, align 8
  %22 = load %"(u32 -> u32 + u32, u32 -> u32)", ptr %1, align 4
  %23 = call %"u32[]" @"map<u32, u32>"(%"u32[]" %a3, %"(u32 -> u32 + u32, u32 -> u32)" %22)
  store %"u32[]" %23, ptr %a24, align 8
  %a25 = load %"u32[]", ptr %a24, align 8
  %24 = call %Unit @"forEach<u32>"(%"u32[]" %a25, ptr @"program::#lambda.1")
  %25 = call %Unit (ptr, ...) @printf(ptr @4)
  %26 = call ptr @malloc(i32 4)
  store i32 0, ptr %26, align 4
  %27 = load ptr, ptr %c, align 8
  %28 = call %Unit @_WriteChannel(ptr %27, ptr %26)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

define %Unit @"fill<boolean>"(%"boolean[]" %0, i1 %1, i32 %2) {
entry:
  %3 = alloca i32, align 4
  %i = alloca i32, align 4
  %num = alloca i32, align 4
  %value = alloca i1, align 1
  %array = alloca %"boolean[]", align 8
  store %"boolean[]" %0, ptr %array, align 8
  store i1 %1, ptr %value, align 1
  store i32 %2, ptr %num, align 4
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %num2 = load i32, ptr %num, align 4
  %4 = icmp slt i32 %i1, %num2
  br i1 %4, label %loop, label %rest13

loop:                                             ; preds = %else8, %entry
  %i3 = load i32, ptr %i, align 4
  %5 = getelementptr %"boolean[]", ptr %array, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  %7 = icmp sle i32 %6, %i3
  br i1 %7, label %then, label %else8

then:                                             ; preds = %loop
  %8 = getelementptr %"boolean[]", ptr %array, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  %10 = icmp sle i32 %9, %i3
  br i1 %10, label %then4, label %else7

then4:                                            ; preds = %then
  %11 = mul nsw i32 %i3, 2
  %12 = getelementptr %"boolean[]", ptr %array, i32 0, i32 1
  %13 = load i32, ptr %12, align 4
  %14 = icmp sge i32 %11, %13
  br i1 %14, label %then5, label %else

then5:                                            ; preds = %then4
  %15 = getelementptr %"boolean[]", ptr %array, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = sext i32 %11 to i64
  %18 = mul nsw i64 %17, 1
  %19 = call ptr @GC_malloc(i64 %18)
  store i32 0, ptr %3, align 4
  %20 = load i32, ptr %3, align 4
  %21 = icmp slt i32 %20, %13
  br i1 %21, label %loop6, label %rest

loop6:                                            ; preds = %loop6, %then5
  %22 = load i32, ptr %3, align 4
  %23 = getelementptr ptr, ptr %19, i32 %22
  %24 = getelementptr i1, ptr %16, i32 %22
  %25 = load i1, ptr %24, align 1
  store i1 %25, ptr %23, align 1
  %26 = add nsw i32 %22, 1
  store i32 %26, ptr %3, align 4
  %27 = load i32, ptr %3, align 4
  %28 = icmp slt i32 %27, %13
  br i1 %28, label %loop6, label %rest

rest:                                             ; preds = %loop6, %then5
  store ptr %19, ptr %15, align 8
  %29 = getelementptr %"boolean[]", ptr %array, i32 0, i32 2
  store i32 %11, ptr %29, align 4
  br label %else

else:                                             ; preds = %rest, %then4
  br label %else7

else7:                                            ; preds = %else, %then
  %30 = add nsw i32 %i3, 1
  store i32 %30, ptr %5, align 4
  br label %else8

else8:                                            ; preds = %else7, %loop
  %31 = getelementptr %"boolean[]", ptr %array, i32 0, i32 0
  %32 = load ptr, ptr %31, align 8
  %33 = getelementptr i1, ptr %32, i32 %i3
  %value9 = load i1, ptr %value, align 1
  store i1 %value9, ptr %33, align 1
  %i10 = load i32, ptr %i, align 4
  %34 = add nsw i32 %i10, 1
  store i32 %34, ptr %i, align 4
  %i11 = load i32, ptr %i, align 4
  %num12 = load i32, ptr %num, align 4
  %35 = icmp slt i32 %i11, %num12
  br i1 %35, label %loop, label %rest13

rest13:                                           ; preds = %else8, %entry
  ret %Unit zeroinitializer
}

declare ptr @GC_malloc(i64)

define %Unit @"fill<u32>"(%"u32[]" %0, i32 %1, i32 %2) {
entry:
  %3 = alloca i32, align 4
  %i = alloca i32, align 4
  %num = alloca i32, align 4
  %value = alloca i32, align 4
  %array = alloca %"u32[]", align 8
  store %"u32[]" %0, ptr %array, align 8
  store i32 %1, ptr %value, align 4
  store i32 %2, ptr %num, align 4
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %num2 = load i32, ptr %num, align 4
  %4 = icmp slt i32 %i1, %num2
  br i1 %4, label %loop, label %rest13

loop:                                             ; preds = %else8, %entry
  %i3 = load i32, ptr %i, align 4
  %5 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  %7 = icmp sle i32 %6, %i3
  br i1 %7, label %then, label %else8

then:                                             ; preds = %loop
  %8 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  %10 = icmp sle i32 %9, %i3
  br i1 %10, label %then4, label %else7

then4:                                            ; preds = %then
  %11 = mul nsw i32 %i3, 2
  %12 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %13 = load i32, ptr %12, align 4
  %14 = icmp sge i32 %11, %13
  br i1 %14, label %then5, label %else

then5:                                            ; preds = %then4
  %15 = getelementptr %"u32[]", ptr %array, i32 0, i32 0
  %16 = load ptr, ptr %15, align 8
  %17 = sext i32 %11 to i64
  %18 = mul nsw i64 %17, 4
  %19 = call ptr @GC_malloc(i64 %18)
  store i32 0, ptr %3, align 4
  %20 = load i32, ptr %3, align 4
  %21 = icmp slt i32 %20, %13
  br i1 %21, label %loop6, label %rest

loop6:                                            ; preds = %loop6, %then5
  %22 = load i32, ptr %3, align 4
  %23 = getelementptr ptr, ptr %19, i32 %22
  %24 = getelementptr i32, ptr %16, i32 %22
  %25 = load i32, ptr %24, align 4
  store i32 %25, ptr %23, align 4
  %26 = add nsw i32 %22, 1
  store i32 %26, ptr %3, align 4
  %27 = load i32, ptr %3, align 4
  %28 = icmp slt i32 %27, %13
  br i1 %28, label %loop6, label %rest

rest:                                             ; preds = %loop6, %then5
  store ptr %19, ptr %15, align 8
  %29 = getelementptr %"u32[]", ptr %array, i32 0, i32 2
  store i32 %11, ptr %29, align 4
  br label %else

else:                                             ; preds = %rest, %then4
  br label %else7

else7:                                            ; preds = %else, %then
  %30 = add nsw i32 %i3, 1
  store i32 %30, ptr %5, align 4
  br label %else8

else8:                                            ; preds = %else7, %loop
  %31 = getelementptr %"u32[]", ptr %array, i32 0, i32 0
  %32 = load ptr, ptr %31, align 8
  %33 = getelementptr i32, ptr %32, i32 %i3
  %value9 = load i32, ptr %value, align 4
  store i32 %value9, ptr %33, align 4
  %i10 = load i32, ptr %i, align 4
  %34 = add nsw i32 %i10, 1
  store i32 %34, ptr %i, align 4
  %i11 = load i32, ptr %i, align 4
  %num12 = load i32, ptr %num, align 4
  %35 = icmp slt i32 %i11, %num12
  br i1 %35, label %loop, label %rest13

rest13:                                           ; preds = %else8, %entry
  ret %Unit zeroinitializer
}

define %Unit @"forEach<u32>"(%"u32[]" %0, ptr %1) {
entry:
  %t = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + u32)", align 8
  %3 = alloca %"(Unit + u32)", align 8
  %4 = alloca %"(Unit + u32)", align 8
  %i = alloca i32, align 4
  %fn = alloca ptr, align 8
  %array = alloca %"u32[]", align 8
  store %"u32[]" %0, ptr %array, align 8
  store ptr %1, ptr %fn, align 8
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %5 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  %7 = icmp slt i32 %i1, %6
  br i1 %7, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, ptr %i, align 4
  %8 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  %10 = icmp slt i32 %i2, %9
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %11 = icmp sge i32 %i2, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr %"u32[]", ptr %array, i32 0, i32 0
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr i32, ptr %13, i32 %i2
  %15 = load i32, ptr %14, align 4
  %16 = getelementptr %"(Unit + u32)", ptr %4, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + u32)", ptr %4, i32 0, i32 1
  store i32 %15, ptr %17, align 4
  %18 = load %"(Unit + u32)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %19 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + u32)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  store %"(Unit + u32)" %arrayAccess, ptr %2, align 4
  %22 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  switch i32 %23, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 1
  %25 = load %Unit, ptr %24, align 1
  store %Unit %25, ptr %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + u32)", ptr %2, i32 0, i32 1
  %27 = load i32, ptr %26, align 4
  store i32 %27, ptr %t, align 4
  %t3 = load i32, ptr %t, align 4
  %fn4 = load ptr, ptr %fn, align 8
  %28 = call %Unit %fn4(i32 %t3)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i5 = load i32, ptr %i, align 4
  %29 = add nsw i32 %i5, 1
  store i32 %29, ptr %i, align 4
  %i6 = load i32, ptr %i, align 4
  %30 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %31 = load i32, ptr %30, align 4
  %32 = icmp slt i32 %i6, %31
  br i1 %32, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}

define %"u32[]" @"map<u32, u32>"(%"u32[]" %0, %"(u32 -> u32 + u32, u32 -> u32)" %1) {
entry:
  %2 = alloca i32, align 4
  %ele.0 = alloca i32, align 4
  %u.0 = alloca %Unit, align 8
  %3 = alloca %"(Unit + u32)", align 8
  %4 = alloca %"(Unit + u32)", align 8
  %5 = alloca %"(Unit + u32)", align 8
  %i.0 = alloca i32, align 4
  %m2 = alloca ptr, align 8
  %6 = alloca i32, align 4
  %ele = alloca i32, align 4
  %u = alloca %Unit, align 8
  %7 = alloca %"(Unit + u32)", align 8
  %8 = alloca %"(Unit + u32)", align 8
  %9 = alloca %"(Unit + u32)", align 8
  %i = alloca i32, align 4
  %m1 = alloca ptr, align 8
  %10 = alloca %"(u32 -> u32 + u32, u32 -> u32)", align 8
  %output = alloca %"u32[]", align 8
  %mapper = alloca %"(u32 -> u32 + u32, u32 -> u32)", align 8
  %array = alloca %"u32[]", align 8
  store %"u32[]" %0, ptr %array, align 8
  store %"(u32 -> u32 + u32, u32 -> u32)" %1, ptr %mapper, align 4
  %11 = getelementptr %"u32[]", ptr %output, i32 0, i32 0
  %12 = sext i32 2 to i64
  %13 = mul nsw i64 %12, 4
  %14 = call ptr @GC_malloc(i64 %13)
  store ptr %14, ptr %11, align 8
  %15 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  store i32 1, ptr %15, align 4
  %16 = getelementptr %"u32[]", ptr %output, i32 0, i32 2
  store i32 2, ptr %16, align 4
  %mapper1 = load %"(u32 -> u32 + u32, u32 -> u32)", ptr %mapper, align 4
  store %"(u32 -> u32 + u32, u32 -> u32)" %mapper1, ptr %10, align 4
  %17 = getelementptr %"(u32 -> u32 + u32, u32 -> u32)", ptr %10, i32 0, i32 0
  %18 = load i32, ptr %17, align 4
  switch i32 %18, label %match-cont43 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch216
  ]

tagBranch1:                                       ; preds = %entry
  %19 = getelementptr %"(u32 -> u32 + u32, u32 -> u32)", ptr %10, i32 0, i32 1
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %m1, align 8
  store i32 0, ptr %i, align 4
  %i2 = load i32, ptr %i, align 4
  %21 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %22 = load i32, ptr %21, align 4
  %23 = icmp slt i32 %i2, %22
  br i1 %23, label %loop, label %rest15

loop:                                             ; preds = %match-cont, %tagBranch1
  %i3 = load i32, ptr %i, align 4
  %24 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %25 = load i32, ptr %24, align 4
  %26 = icmp slt i32 %i3, %25
  br i1 %26, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %27 = icmp sge i32 %i3, 0
  br i1 %27, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %28 = getelementptr %"u32[]", ptr %array, i32 0, i32 0
  %29 = load ptr, ptr %28, align 8
  %30 = getelementptr i32, ptr %29, i32 %i3
  %31 = load i32, ptr %30, align 4
  %32 = getelementptr %"(Unit + u32)", ptr %9, i32 0, i32 0
  store i32 2, ptr %32, align 4
  %33 = getelementptr %"(Unit + u32)", ptr %9, i32 0, i32 1
  store i32 %31, ptr %33, align 4
  %34 = load %"(Unit + u32)", ptr %9, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %35 = getelementptr %"(Unit + u32)", ptr %8, i32 0, i32 0
  store i32 1, ptr %35, align 4
  %36 = getelementptr %"(Unit + u32)", ptr %8, i32 0, i32 1
  store %Unit zeroinitializer, ptr %36, align 1
  %37 = load %"(Unit + u32)", ptr %8, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + u32)" [ %34, %accessGTZ ], [ %37, %accessBad ]
  store %"(Unit + u32)" %arrayAccess, ptr %7, align 4
  %38 = getelementptr %"(Unit + u32)", ptr %7, i32 0, i32 0
  %39 = load i32, ptr %38, align 4
  switch i32 %39, label %match-cont [
    i32 1, label %tagBranch14
    i32 2, label %tagBranch2
  ]

tagBranch14:                                      ; preds = %accessAfter
  %40 = getelementptr %"(Unit + u32)", ptr %7, i32 0, i32 1
  %41 = load %Unit, ptr %40, align 1
  store %Unit %41, ptr %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %42 = getelementptr %"(Unit + u32)", ptr %7, i32 0, i32 1
  %43 = load i32, ptr %42, align 4
  store i32 %43, ptr %ele, align 4
  %i5 = load i32, ptr %i, align 4
  %44 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  %45 = load i32, ptr %44, align 4
  %46 = icmp sle i32 %45, %i5
  br i1 %46, label %then, label %else10

then:                                             ; preds = %tagBranch2
  %47 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  %48 = load i32, ptr %47, align 4
  %49 = icmp sle i32 %48, %i5
  br i1 %49, label %then6, label %else9

then6:                                            ; preds = %then
  %50 = mul nsw i32 %i5, 2
  %51 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  %52 = load i32, ptr %51, align 4
  %53 = icmp sge i32 %50, %52
  br i1 %53, label %then7, label %else

then7:                                            ; preds = %then6
  %54 = getelementptr %"u32[]", ptr %output, i32 0, i32 0
  %55 = load ptr, ptr %54, align 8
  %56 = sext i32 %50 to i64
  %57 = mul nsw i64 %56, 4
  %58 = call ptr @GC_malloc(i64 %57)
  store i32 0, ptr %6, align 4
  %59 = load i32, ptr %6, align 4
  %60 = icmp slt i32 %59, %52
  br i1 %60, label %loop8, label %rest

loop8:                                            ; preds = %loop8, %then7
  %61 = load i32, ptr %6, align 4
  %62 = getelementptr ptr, ptr %58, i32 %61
  %63 = getelementptr i32, ptr %55, i32 %61
  %64 = load i32, ptr %63, align 4
  store i32 %64, ptr %62, align 4
  %65 = add nsw i32 %61, 1
  store i32 %65, ptr %6, align 4
  %66 = load i32, ptr %6, align 4
  %67 = icmp slt i32 %66, %52
  br i1 %67, label %loop8, label %rest

rest:                                             ; preds = %loop8, %then7
  store ptr %58, ptr %54, align 8
  %68 = getelementptr %"u32[]", ptr %output, i32 0, i32 2
  store i32 %50, ptr %68, align 4
  br label %else

else:                                             ; preds = %rest, %then6
  br label %else9

else9:                                            ; preds = %else, %then
  %69 = add nsw i32 %i5, 1
  store i32 %69, ptr %44, align 4
  br label %else10

else10:                                           ; preds = %else9, %tagBranch2
  %70 = getelementptr %"u32[]", ptr %output, i32 0, i32 0
  %71 = load ptr, ptr %70, align 8
  %72 = getelementptr i32, ptr %71, i32 %i5
  %ele11 = load i32, ptr %ele, align 4
  %m112 = load ptr, ptr %m1, align 8
  %73 = call i32 %m112(i32 %ele11)
  store i32 %73, ptr %72, align 4
  br label %match-cont

match-cont:                                       ; preds = %else10, %tagBranch14, %accessAfter
  %i13 = load i32, ptr %i, align 4
  %74 = add nsw i32 %i13, 1
  store i32 %74, ptr %i, align 4
  %i14 = load i32, ptr %i, align 4
  %75 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %76 = load i32, ptr %75, align 4
  %77 = icmp slt i32 %i14, %76
  br i1 %77, label %loop, label %rest15

rest15:                                           ; preds = %match-cont, %tagBranch1
  br label %match-cont43

tagBranch216:                                     ; preds = %entry
  %78 = getelementptr %"(u32 -> u32 + u32, u32 -> u32)", ptr %10, i32 0, i32 1
  %79 = load ptr, ptr %78, align 8
  store ptr %79, ptr %m2, align 8
  store i32 0, ptr %i.0, align 4
  %i.017 = load i32, ptr %i.0, align 4
  %80 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %81 = load i32, ptr %80, align 4
  %82 = icmp slt i32 %i.017, %81
  br i1 %82, label %loop18, label %rest42

loop18:                                           ; preds = %match-cont39, %tagBranch216
  %i.019 = load i32, ptr %i.0, align 4
  %83 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %84 = load i32, ptr %83, align 4
  %85 = icmp slt i32 %i.019, %84
  br i1 %85, label %accessLTL20, label %accessBad22

accessLTL20:                                      ; preds = %loop18
  %86 = icmp sge i32 %i.019, 0
  br i1 %86, label %accessGTZ21, label %accessBad22

accessGTZ21:                                      ; preds = %accessLTL20
  %87 = getelementptr %"u32[]", ptr %array, i32 0, i32 0
  %88 = load ptr, ptr %87, align 8
  %89 = getelementptr i32, ptr %88, i32 %i.019
  %90 = load i32, ptr %89, align 4
  %91 = getelementptr %"(Unit + u32)", ptr %5, i32 0, i32 0
  store i32 2, ptr %91, align 4
  %92 = getelementptr %"(Unit + u32)", ptr %5, i32 0, i32 1
  store i32 %90, ptr %92, align 4
  %93 = load %"(Unit + u32)", ptr %5, align 4
  br label %accessAfter23

accessBad22:                                      ; preds = %accessLTL20, %loop18
  %94 = getelementptr %"(Unit + u32)", ptr %4, i32 0, i32 0
  store i32 1, ptr %94, align 4
  %95 = getelementptr %"(Unit + u32)", ptr %4, i32 0, i32 1
  store %Unit zeroinitializer, ptr %95, align 1
  %96 = load %"(Unit + u32)", ptr %4, align 4
  br label %accessAfter23

accessAfter23:                                    ; preds = %accessBad22, %accessGTZ21
  %arrayAccess24 = phi %"(Unit + u32)" [ %93, %accessGTZ21 ], [ %96, %accessBad22 ]
  store %"(Unit + u32)" %arrayAccess24, ptr %3, align 4
  %97 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 0
  %98 = load i32, ptr %97, align 4
  switch i32 %98, label %match-cont39 [
    i32 1, label %tagBranch125
    i32 2, label %tagBranch226
  ]

tagBranch125:                                     ; preds = %accessAfter23
  %99 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 1
  %100 = load %Unit, ptr %99, align 1
  store %Unit %100, ptr %u.0, align 1
  br label %match-cont39

tagBranch226:                                     ; preds = %accessAfter23
  %101 = getelementptr %"(Unit + u32)", ptr %3, i32 0, i32 1
  %102 = load i32, ptr %101, align 4
  store i32 %102, ptr %ele.0, align 4
  %i.027 = load i32, ptr %i.0, align 4
  %103 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  %104 = load i32, ptr %103, align 4
  %105 = icmp sle i32 %104, %i.027
  br i1 %105, label %then28, label %else35

then28:                                           ; preds = %tagBranch226
  %106 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  %107 = load i32, ptr %106, align 4
  %108 = icmp sle i32 %107, %i.027
  br i1 %108, label %then29, label %else34

then29:                                           ; preds = %then28
  %109 = mul nsw i32 %i.027, 2
  %110 = getelementptr %"u32[]", ptr %output, i32 0, i32 1
  %111 = load i32, ptr %110, align 4
  %112 = icmp sge i32 %109, %111
  br i1 %112, label %then30, label %else33

then30:                                           ; preds = %then29
  %113 = getelementptr %"u32[]", ptr %output, i32 0, i32 0
  %114 = load ptr, ptr %113, align 8
  %115 = sext i32 %109 to i64
  %116 = mul nsw i64 %115, 4
  %117 = call ptr @GC_malloc(i64 %116)
  store i32 0, ptr %2, align 4
  %118 = load i32, ptr %2, align 4
  %119 = icmp slt i32 %118, %111
  br i1 %119, label %loop31, label %rest32

loop31:                                           ; preds = %loop31, %then30
  %120 = load i32, ptr %2, align 4
  %121 = getelementptr ptr, ptr %117, i32 %120
  %122 = getelementptr i32, ptr %114, i32 %120
  %123 = load i32, ptr %122, align 4
  store i32 %123, ptr %121, align 4
  %124 = add nsw i32 %120, 1
  store i32 %124, ptr %2, align 4
  %125 = load i32, ptr %2, align 4
  %126 = icmp slt i32 %125, %111
  br i1 %126, label %loop31, label %rest32

rest32:                                           ; preds = %loop31, %then30
  store ptr %117, ptr %113, align 8
  %127 = getelementptr %"u32[]", ptr %output, i32 0, i32 2
  store i32 %109, ptr %127, align 4
  br label %else33

else33:                                           ; preds = %rest32, %then29
  br label %else34

else34:                                           ; preds = %else33, %then28
  %128 = add nsw i32 %i.027, 1
  store i32 %128, ptr %103, align 4
  br label %else35

else35:                                           ; preds = %else34, %tagBranch226
  %129 = getelementptr %"u32[]", ptr %output, i32 0, i32 0
  %130 = load ptr, ptr %129, align 8
  %131 = getelementptr i32, ptr %130, i32 %i.027
  %ele.036 = load i32, ptr %ele.0, align 4
  %i.037 = load i32, ptr %i.0, align 4
  %m238 = load ptr, ptr %m2, align 8
  %132 = call i32 %m238(i32 %ele.036, i32 %i.037)
  store i32 %132, ptr %131, align 4
  br label %match-cont39

match-cont39:                                     ; preds = %else35, %tagBranch125, %accessAfter23
  %i.040 = load i32, ptr %i.0, align 4
  %133 = add nsw i32 %i.040, 1
  store i32 %133, ptr %i.0, align 4
  %i.041 = load i32, ptr %i.0, align 4
  %134 = getelementptr %"u32[]", ptr %array, i32 0, i32 1
  %135 = load i32, ptr %134, align 4
  %136 = icmp slt i32 %i.041, %135
  br i1 %136, label %loop18, label %rest42

rest42:                                           ; preds = %match-cont39, %tagBranch216
  br label %match-cont43

match-cont43:                                     ; preds = %rest42, %rest15, %entry
  %output44 = load %"u32[]", ptr %output, align 8
  ret %"u32[]" %output44
}

define private %Unit @"program::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call %Unit (ptr, ...) @printf(ptr @1, i32 %i1)
  ret %Unit zeroinitializer
}

define private i32 @"program::#lambda.0"(i32 %0, i32 %1) {
entry:
  %idx = alloca i32, align 4
  %ele = alloca i32, align 4
  store i32 %0, ptr %ele, align 4
  store i32 %1, ptr %idx, align 4
  %idx1 = load i32, ptr %idx, align 4
  ret i32 %idx1
}

define private %Unit @"program::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call %Unit (ptr, ...) @printf(ptr @3, i32 %i1)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
