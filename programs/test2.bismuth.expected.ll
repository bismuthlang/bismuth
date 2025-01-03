; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

@0 = private unnamed_addr constant [33 x i8] c"Int equality test I: %d, %d, %d\0A\00", align 1
@1 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@2 = private unnamed_addr constant [9 x i8] c"a := 95\0A\00", align 1
@3 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@4 = private unnamed_addr constant [26 x i8] c"b := -37 * (12-2) = -370\0A\00", align 1
@5 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@6 = private unnamed_addr constant [12 x i8] c"c := %d/%d\0A\00", align 1
@7 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@8 = private unnamed_addr constant [34 x i8] c"Int equality test II: %d, %d, %d\0A\00", align 1
@9 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@10 = private unnamed_addr constant [34 x i8] c"bool equality test I: %d, %d, %d\0A\00", align 1
@11 = private unnamed_addr constant [16 x i8] c"a := !(b || c)\0A\00", align 1
@12 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@13 = private unnamed_addr constant [13 x i8] c"b := b || c\0A\00", align 1
@14 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@15 = private unnamed_addr constant [15 x i8] c"c := !a && !b\0A\00", align 1
@16 = private unnamed_addr constant [24 x i8] c"a = %d, b = %d, c = %d\0A\00", align 1
@17 = private unnamed_addr constant [35 x i8] c"bool equality test II: %d, %d, %d\0A\00", align 1
@18 = private unnamed_addr constant [11 x i8] c"String One\00", align 1
@19 = private unnamed_addr constant [11 x i8] c"String One\00", align 1
@20 = private unnamed_addr constant [11 x i8] c"String Two\00", align 1
@21 = private unnamed_addr constant [24 x i8] c"a = %s, b = %s, c = %s\0A\00", align 1
@22 = private unnamed_addr constant [33 x i8] c"str equality test I: %d, %d, %d\0A\00", align 1
@23 = private unnamed_addr constant [13 x i8] c"String 3 now\00", align 1
@24 = private unnamed_addr constant [24 x i8] c"a = %s, b = %s, c = %s\0A\00", align 1
@25 = private unnamed_addr constant [34 x i8] c"str equality test II: %d, %d, %d\0A\00", align 1
@26 = private unnamed_addr constant [40 x i8] c"Ints still are: a = %d, b = %d, c = %d\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %c.1 = alloca ptr, align 8
  %b.1 = alloca ptr, align 8
  %a.1 = alloca ptr, align 8
  %c.0 = alloca i1, align 1
  %b.0 = alloca i1, align 1
  %a.0 = alloca i1, align 1
  %c = alloca i32, align 4
  %b = alloca i32, align 4
  %a = alloca i32, align 4
  %io = alloca ptr, align 8
  store ptr %0, ptr %io, align 8
  store i32 10, ptr %a, align 4
  store i32 10, ptr %b, align 4
  store i32 10, ptr %c, align 4
  %a1 = load i32, ptr %a, align 4
  %b2 = load i32, ptr %b, align 4
  %1 = icmp eq i32 %a1, %b2
  %a3 = load i32, ptr %a, align 4
  %b4 = load i32, ptr %b, align 4
  %2 = icmp ne i32 %a3, %b4
  %a5 = load i32, ptr %a, align 4
  %c6 = load i32, ptr %c, align 4
  %3 = icmp eq i32 %a5, %c6
  %4 = call i32 (...) @printf(ptr @0, i1 %1, i1 %2, i1 %3)
  %a7 = load i32, ptr %a, align 4
  %b8 = load i32, ptr %b, align 4
  %c9 = load i32, ptr %c, align 4
  %5 = call i32 (...) @printf(ptr @1, i32 %a7, i32 %b8, i32 %c9)
  store i32 95, ptr %a, align 4
  %6 = call i32 (...) @printf(ptr @2)
  %a10 = load i32, ptr %a, align 4
  %b11 = load i32, ptr %b, align 4
  %c12 = load i32, ptr %c, align 4
  %7 = call i32 (...) @printf(ptr @3, i32 %a10, i32 %b11, i32 %c12)
  %8 = sub nsw i32 0, 37
  %9 = sdiv i32 10, 2
  %10 = mul nsw i32 %8, %9
  store i32 %10, ptr %b, align 4
  %11 = call i32 (...) @printf(ptr @4)
  %a13 = load i32, ptr %a, align 4
  %b14 = load i32, ptr %b, align 4
  %c15 = load i32, ptr %c, align 4
  %12 = call i32 (...) @printf(ptr @5, i32 %a13, i32 %b14, i32 %c15)
  %a16 = load i32, ptr %a, align 4
  %b17 = load i32, ptr %b, align 4
  %13 = sdiv i32 %a16, %b17
  store i32 %13, ptr %c, align 4
  %a18 = load i32, ptr %a, align 4
  %b19 = load i32, ptr %b, align 4
  %14 = call i32 (...) @printf(ptr @6, i32 %a18, i32 %b19)
  %a20 = load i32, ptr %a, align 4
  %b21 = load i32, ptr %b, align 4
  %c22 = load i32, ptr %c, align 4
  %15 = call i32 (...) @printf(ptr @7, i32 %a20, i32 %b21, i32 %c22)
  %a23 = load i32, ptr %a, align 4
  %b24 = load i32, ptr %b, align 4
  %16 = icmp eq i32 %a23, %b24
  %a25 = load i32, ptr %a, align 4
  %b26 = load i32, ptr %b, align 4
  %17 = icmp ne i32 %a25, %b26
  %a27 = load i32, ptr %a, align 4
  %c28 = load i32, ptr %c, align 4
  %18 = icmp eq i32 %a27, %c28
  %19 = call i32 (...) @printf(ptr @8, i1 %16, i1 %17, i1 %18)
  store i1 true, ptr %a.0, align 1
  store i1 true, ptr %b.0, align 1
  store i1 false, ptr %c.0, align 1
  %a.029 = load i1, ptr %a.0, align 1
  %b.030 = load i1, ptr %b.0, align 1
  %c.031 = load i1, ptr %c.0, align 1
  %20 = call i32 (...) @printf(ptr @9, i1 %a.029, i1 %b.030, i1 %c.031)
  %a.032 = load i1, ptr %a.0, align 1
  %b.033 = load i1, ptr %b.0, align 1
  %21 = icmp eq i1 %a.032, %b.033
  %a.034 = load i1, ptr %a.0, align 1
  %b.035 = load i1, ptr %b.0, align 1
  %22 = icmp ne i1 %a.034, %b.035
  %a.036 = load i1, ptr %a.0, align 1
  %c.037 = load i1, ptr %c.0, align 1
  %23 = icmp eq i1 %a.036, %c.037
  %24 = call i32 (...) @printf(ptr @10, i1 %21, i1 %22, i1 %23)
  %b.038 = load i1, ptr %b.0, align 1
  br i1 %b.038, label %mergeBlkOr, label %prevFalseOr

prevFalseOr:                                      ; preds = %entry
  %c.039 = load i1, ptr %c.0, align 1
  br label %mergeBlkOr

mergeBlkOr:                                       ; preds = %prevFalseOr, %entry
  %logOr = phi i1 [ %b.038, %entry ], [ %c.039, %prevFalseOr ]
  %25 = xor i1 %logOr, true
  store i1 %25, ptr %a.0, align 1
  %26 = call i32 (...) @printf(ptr @11)
  %a.040 = load i1, ptr %a.0, align 1
  %b.041 = load i1, ptr %b.0, align 1
  %c.042 = load i1, ptr %c.0, align 1
  %27 = call i32 (...) @printf(ptr @12, i1 %a.040, i1 %b.041, i1 %c.042)
  %b.043 = load i1, ptr %b.0, align 1
  br i1 %b.043, label %mergeBlkOr47, label %prevFalseOr44

prevFalseOr44:                                    ; preds = %mergeBlkOr
  %c.045 = load i1, ptr %c.0, align 1
  br label %mergeBlkOr47

mergeBlkOr47:                                     ; preds = %prevFalseOr44, %mergeBlkOr
  %logOr46 = phi i1 [ %b.043, %mergeBlkOr ], [ %c.045, %prevFalseOr44 ]
  store i1 %logOr46, ptr %b.0, align 1
  %28 = call i32 (...) @printf(ptr @13)
  %a.048 = load i1, ptr %a.0, align 1
  %b.049 = load i1, ptr %b.0, align 1
  %c.050 = load i1, ptr %c.0, align 1
  %29 = call i32 (...) @printf(ptr @14, i1 %a.048, i1 %b.049, i1 %c.050)
  %a.051 = load i1, ptr %a.0, align 1
  %30 = xor i1 %a.051, true
  br i1 %30, label %prevTrueAnd, label %mergeBlkAnd

prevTrueAnd:                                      ; preds = %mergeBlkOr47
  %b.052 = load i1, ptr %b.0, align 1
  %31 = xor i1 %b.052, true
  br label %mergeBlkAnd

mergeBlkAnd:                                      ; preds = %prevTrueAnd, %mergeBlkOr47
  %logAnd = phi i1 [ %30, %mergeBlkOr47 ], [ %31, %prevTrueAnd ]
  store i1 %logAnd, ptr %c.0, align 1
  %32 = call i32 (...) @printf(ptr @15)
  %a.053 = load i1, ptr %a.0, align 1
  %b.054 = load i1, ptr %b.0, align 1
  %c.055 = load i1, ptr %c.0, align 1
  %33 = call i32 (...) @printf(ptr @16, i1 %a.053, i1 %b.054, i1 %c.055)
  %a.056 = load i1, ptr %a.0, align 1
  %b.057 = load i1, ptr %b.0, align 1
  %34 = icmp eq i1 %a.056, %b.057
  %a.058 = load i1, ptr %a.0, align 1
  %b.059 = load i1, ptr %b.0, align 1
  %35 = icmp ne i1 %a.058, %b.059
  %a.060 = load i1, ptr %a.0, align 1
  %c.061 = load i1, ptr %c.0, align 1
  %36 = icmp eq i1 %a.060, %c.061
  %37 = call i32 (...) @printf(ptr @17, i1 %34, i1 %35, i1 %36)
  store ptr @18, ptr %a.1, align 8
  store ptr @19, ptr %b.1, align 8
  store ptr @20, ptr %c.1, align 8
  %a.162 = load ptr, ptr %a.1, align 8
  %b.163 = load ptr, ptr %b.1, align 8
  %c.164 = load ptr, ptr %c.1, align 8
  %38 = call i32 (...) @printf(ptr @21, ptr %a.162, ptr %b.163, ptr %c.164)
  %a.165 = load ptr, ptr %a.1, align 8
  %b.166 = load ptr, ptr %b.1, align 8
  %39 = icmp eq ptr %a.165, %b.166
  %a.167 = load ptr, ptr %a.1, align 8
  %b.168 = load ptr, ptr %b.1, align 8
  %40 = icmp ne ptr %a.167, %b.168
  %a.169 = load ptr, ptr %a.1, align 8
  %c.170 = load ptr, ptr %c.1, align 8
  %41 = icmp eq ptr %a.169, %c.170
  %42 = call i32 (...) @printf(ptr @22, i1 %39, i1 %40, i1 %41)
  store ptr @23, ptr %a.1, align 8
  %a.171 = load ptr, ptr %a.1, align 8
  %b.172 = load ptr, ptr %b.1, align 8
  %c.173 = load ptr, ptr %c.1, align 8
  %43 = call i32 (...) @printf(ptr @24, ptr %a.171, ptr %b.172, ptr %c.173)
  %a.174 = load ptr, ptr %a.1, align 8
  %b.175 = load ptr, ptr %b.1, align 8
  %44 = icmp eq ptr %a.174, %b.175
  %a.176 = load ptr, ptr %a.1, align 8
  %b.177 = load ptr, ptr %b.1, align 8
  %45 = icmp ne ptr %a.176, %b.177
  %a.178 = load ptr, ptr %a.1, align 8
  %c.179 = load ptr, ptr %c.1, align 8
  %46 = icmp eq ptr %a.178, %c.179
  %47 = call i32 (...) @printf(ptr @25, i1 %44, i1 %45, i1 %46)
  %a80 = load i32, ptr %a, align 4
  %b81 = load i32, ptr %b, align 4
  %c82 = load i32, ptr %c, align 4
  %48 = call i32 (...) @printf(ptr @26, i32 %a80, i32 %b81, i32 %c82)
  %49 = sub nsw i32 0, 1
  %50 = call ptr @malloc(i32 4)
  store i32 %49, ptr %50, align 4
  %51 = load ptr, ptr %io, align 8
  %52 = call %Unit @_WriteChannel(ptr %51, ptr %50)
  ret %Unit zeroinitializer
}

declare i32 @printf(...)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
