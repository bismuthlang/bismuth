; ModuleID = 'WPLC.ll'
source_filename = "WPLC.ll"

define i32 @pow(i32 %0, i32 %1) {
entry:
  %intnumber = alloca i32, align 4
  store i32 %0, i32* %intnumber, align 4
  %intpower = alloca i32, align 4
  store i32 %1, i32* %intpower, align 4
  %power = load i32, i32* %intpower, align 4
  %2 = icmp eq i32 %power, 0
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  ret i32 1

else:                                             ; preds = %entry
  %power1 = load i32, i32* %intpower, align 4
  %3 = icmp slt i32 %power1, 0
  br i1 %3, label %then2, label %else3

then2:                                            ; preds = %else
  ret i32 0

else3:                                            ; preds = %else
  %ans = alloca i32, align 4
  store i32 1, i32* %ans, align 4
  %power4 = load i32, i32* %intpower, align 4
  %4 = icmp sge i32 %power4, 1
  br i1 %4, label %loop, label %rest

loop:                                             ; preds = %loop, %else3
  %ans5 = load i32, i32* %ans, align 4
  %number = load i32, i32* %intnumber, align 4
  %5 = mul nsw i32 %ans5, %number
  store i32 %5, i32* %ans, align 4
  %power6 = load i32, i32* %intpower, align 4
  %6 = sub nsw i32 %power6, 1
  store i32 %6, i32* %intpower, align 4
  %power7 = load i32, i32* %intpower, align 4
  %7 = icmp sge i32 %power7, 1
  br i1 %7, label %loop, label %rest

rest:                                             ; preds = %loop, %else3
  %ans8 = load i32, i32* %ans, align 4
  ret i32 %ans8
}
