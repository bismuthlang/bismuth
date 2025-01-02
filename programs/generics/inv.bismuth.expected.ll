; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%LAM = type {}
%"int[]" = type { ptr, i32, i32 }
%"(boolean + int)" = type { i32, [4 x i8] }
%"boolean[]" = type { ptr, i32, i32 }
%"(boolean + )" = type { i32, [1 x i8] }
%"str[]" = type { ptr, i32, i32 }
%"(boolean + str)" = type { i32, [8 x i8] }

define %Unit @program(ptr %0) {
entry:
  %hmm3 = alloca ptr, align 8
  %hmm2 = alloca ptr, align 8
  %hmm = alloca ptr, align 8
  %a = alloca %LAM, align 8
  %1 = alloca %LAM, align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %2 = load %LAM, ptr %1, align 1
  store %LAM %2, ptr %a, align 1
  %3 = call ptr @malloc(i32 4)
  store i32 0, ptr %3, align 4
  %4 = load ptr, ptr %c, align 8
  %5 = call %Unit @_WriteChannel(ptr %4, ptr %3)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)

define %Unit @"foo<int>"(i32 %0) {
entry:
  %lambda2 = alloca ptr, align 8
  %lambda = alloca ptr, align 8
  %idk2 = alloca ptr, align 8
  %idk = alloca ptr, align 8
  %lambda3 = alloca ptr, align 8
  %abc = alloca %"int[]", align 8
  %sum = alloca %"(boolean + int)", align 8
  %t = alloca i32, align 4
  store i32 %0, ptr %t, align 4
  %1 = sext i32 2 to i64
  %2 = mul nsw i64 %1, 4
  %3 = call ptr @GC_malloc(i64 %2)
  %4 = getelementptr %"int[]", ptr %abc, i32 0, i32 0
  store ptr %3, ptr %4, align 8
  %5 = getelementptr %"int[]", ptr %abc, i32 0, i32 1
  store i32 1, ptr %5, align 4
  %6 = getelementptr %"int[]", ptr %abc, i32 0, i32 2
  store i32 2, ptr %6, align 4
  store ptr @"foo<int>::#lambda", ptr %lambda3, align 8
  store ptr @"foo<int>::#lambda.0", ptr %lambda, align 8
  store ptr @"foo<int>::#lambda.1", ptr %lambda2, align 8
  ret %Unit zeroinitializer
}

declare ptr @GC_malloc(i64)

define private %Unit @"foo<int>::#lambda"(i32 %0) {
entry:
  %a = alloca i32, align 4
  %t = alloca i32, align 4
  store i32 %0, ptr %t, align 4
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private %Unit @"foo<int>::nested<int>"(i32 %0) {
entry:
  %a = alloca i32, align 4
  %param = alloca i32, align 4
  store i32 %0, ptr %param, align 4
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private %Unit @"foo<int>::nested<str>"(ptr %0) {
entry:
  %a = alloca i32, align 4
  %param = alloca ptr, align 8
  store ptr %0, ptr %param, align 8
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private i32 @"foo<int>::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}

define private i32 @"foo<int>::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}

define %Unit @"foo<boolean>"(i1 %0) {
entry:
  %lambda2 = alloca ptr, align 8
  %lambda = alloca ptr, align 8
  %idk2 = alloca ptr, align 8
  %idk = alloca ptr, align 8
  %lambda3 = alloca ptr, align 8
  %abc = alloca %"boolean[]", align 8
  %sum = alloca %"(boolean + )", align 8
  %t = alloca i1, align 1
  store i1 %0, ptr %t, align 1
  %1 = sext i32 2 to i64
  %2 = mul nsw i64 %1, 1
  %3 = call ptr @GC_malloc(i64 %2)
  %4 = getelementptr %"boolean[]", ptr %abc, i32 0, i32 0
  store ptr %3, ptr %4, align 8
  %5 = getelementptr %"boolean[]", ptr %abc, i32 0, i32 1
  store i32 1, ptr %5, align 4
  %6 = getelementptr %"boolean[]", ptr %abc, i32 0, i32 2
  store i32 2, ptr %6, align 4
  store ptr @"foo<boolean>::#lambda", ptr %lambda3, align 8
  store ptr @"foo<boolean>::#lambda.0", ptr %lambda, align 8
  store ptr @"foo<boolean>::#lambda.1", ptr %lambda2, align 8
  ret %Unit zeroinitializer
}

define private %Unit @"foo<boolean>::#lambda"(i1 %0) {
entry:
  %a = alloca i32, align 4
  %t = alloca i1, align 1
  store i1 %0, ptr %t, align 1
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private %Unit @"foo<boolean>::nested<int>"(i32 %0) {
entry:
  %a = alloca i32, align 4
  %param = alloca i32, align 4
  store i32 %0, ptr %param, align 4
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private %Unit @"foo<boolean>::nested<str>"(ptr %0) {
entry:
  %a = alloca i32, align 4
  %param = alloca ptr, align 8
  store ptr %0, ptr %param, align 8
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private i32 @"foo<boolean>::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}

define private i32 @"foo<boolean>::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}

define %Unit @"foo<str>"(ptr %0) {
entry:
  %lambda2 = alloca ptr, align 8
  %lambda = alloca ptr, align 8
  %idk2 = alloca ptr, align 8
  %idk = alloca ptr, align 8
  %lambda3 = alloca ptr, align 8
  %abc = alloca %"str[]", align 8
  %sum = alloca %"(boolean + str)", align 8
  %t = alloca ptr, align 8
  store ptr %0, ptr %t, align 8
  %1 = sext i32 2 to i64
  %2 = mul nsw i64 %1, 8
  %3 = call ptr @GC_malloc(i64 %2)
  %4 = getelementptr %"str[]", ptr %abc, i32 0, i32 0
  store ptr %3, ptr %4, align 8
  %5 = getelementptr %"str[]", ptr %abc, i32 0, i32 1
  store i32 1, ptr %5, align 4
  %6 = getelementptr %"str[]", ptr %abc, i32 0, i32 2
  store i32 2, ptr %6, align 4
  store ptr @"foo<str>::#lambda", ptr %lambda3, align 8
  store ptr @"foo<str>::#lambda.0", ptr %lambda, align 8
  store ptr @"foo<str>::#lambda.1", ptr %lambda2, align 8
  ret %Unit zeroinitializer
}

define private %Unit @"foo<str>::#lambda"(ptr %0) {
entry:
  %a = alloca i32, align 4
  %t = alloca ptr, align 8
  store ptr %0, ptr %t, align 8
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private %Unit @"foo<str>::nested<int>"(i32 %0) {
entry:
  %a = alloca i32, align 4
  %param = alloca i32, align 4
  store i32 %0, ptr %param, align 4
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private %Unit @"foo<str>::nested<str>"(ptr %0) {
entry:
  %a = alloca i32, align 4
  %param = alloca ptr, align 8
  store ptr %0, ptr %param, align 8
  store i32 0, ptr %a, align 4
  ret %Unit zeroinitializer
}

define private i32 @"foo<str>::#lambda.0"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}

define private i32 @"foo<str>::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  ret i32 %i1
}
