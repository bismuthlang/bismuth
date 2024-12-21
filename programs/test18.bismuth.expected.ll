; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"(Unit + int)" = type { i32, [4 x i8] }

@0 = private unnamed_addr constant [13 x i8] c"Hello world!\00", align 1
@1 = private unnamed_addr constant [13 x i8] c"Hello world!\00", align 1
@2 = private unnamed_addr constant [32 x i8] c"a = %s, b = %s, c = %d, d = %d\0A\00", align 1
@3 = private unnamed_addr constant [9 x i8] c"Goodbye!\00", align 1
@4 = private unnamed_addr constant [32 x i8] c"a = %s, b = %s, c = %d, d = %d\0A\00", align 1
@5 = private unnamed_addr constant [22 x i8] c"e[0] = %d, f[0] = %d\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %1 = alloca %"(Unit + int)", align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %f = alloca [5 x i32], align 4
  %e = alloca [5 x i32], align 4
  %d = alloca i32, align 4
  %c = alloca i32, align 4
  %b = alloca ptr, align 8
  %a = alloca ptr, align 8
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  store ptr @0, ptr %a, align 8
  store ptr @1, ptr %b, align 8
  %5 = mul nsw i32 10, 2
  store i32 %5, ptr %c, align 4
  %6 = mul nsw i32 10, 2
  store i32 %6, ptr %d, align 4
  %a1 = load ptr, ptr %a, align 8
  %b2 = load ptr, ptr %b, align 8
  %c3 = load i32, ptr %c, align 4
  %d4 = load i32, ptr %d, align 4
  %7 = call i32 (...) @printf(ptr @2, ptr %a1, ptr %b2, i32 %c3, i32 %d4)
  store ptr @3, ptr %b, align 8
  %d5 = load i32, ptr %d, align 4
  %8 = add nsw i32 %d5, 10
  store i32 %8, ptr %d, align 4
  %a6 = load ptr, ptr %a, align 8
  %b7 = load ptr, ptr %b, align 8
  %c8 = load i32, ptr %c, align 4
  %d9 = load i32, ptr %d, align 4
  %9 = call i32 (...) @printf(ptr @4, ptr %a6, ptr %b7, i32 %c8, i32 %d9)
  %10 = getelementptr [5 x i32], ptr %e, i32 0, i32 0
  store i32 3, ptr %10, align 4
  %11 = getelementptr [5 x i32], ptr %f, i32 0, i32 0
  store i32 1, ptr %11, align 4
  %12 = icmp slt i32 0, 5
  br i1 %12, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %entry
  %13 = icmp sge i32 0, 0
  br i1 %13, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %14 = getelementptr [5 x i32], ptr %e, i32 0, i32 0
  %15 = load i32, ptr %14, align 4
  %16 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 1
  store i32 %15, ptr %17, align 4
  %18 = load %"(Unit + int)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %entry
  %19 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  %22 = icmp slt i32 0, 5
  br i1 %22, label %accessLTL10, label %accessBad12

accessLTL10:                                      ; preds = %accessAfter
  %23 = icmp sge i32 0, 0
  br i1 %23, label %accessGTZ11, label %accessBad12

accessGTZ11:                                      ; preds = %accessLTL10
  %24 = getelementptr [5 x i32], ptr %f, i32 0, i32 0
  %25 = load i32, ptr %24, align 4
  %26 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  store i32 2, ptr %26, align 4
  %27 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  store i32 %25, ptr %27, align 4
  %28 = load %"(Unit + int)", ptr %2, align 4
  br label %accessAfter13

accessBad12:                                      ; preds = %accessLTL10, %accessAfter
  %29 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 0
  store i32 1, ptr %29, align 4
  %30 = getelementptr %"(Unit + int)", ptr %1, i32 0, i32 1
  store %Unit zeroinitializer, ptr %30, align 1
  %31 = load %"(Unit + int)", ptr %1, align 4
  br label %accessAfter13

accessAfter13:                                    ; preds = %accessBad12, %accessGTZ11
  %arrayAccess14 = phi %"(Unit + int)" [ %28, %accessGTZ11 ], [ %31, %accessBad12 ]
  %32 = call i32 (...) @printf(ptr @5, %"(Unit + int)" %arrayAccess, %"(Unit + int)" %arrayAccess14)
  %33 = sub nsw i32 0, 1
  %34 = call ptr @malloc(i32 4)
  store i32 %33, ptr %34, align 4
  %35 = load ptr, ptr %io, align 8
  %36 = call %Unit @_WriteChannel(ptr %35, ptr %34)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
