; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}

define %Unit @program(ptr %0) {
entry:
  %result = alloca i32, align 4
  %i = alloca i32, align 4
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %1 = call i32 @getIntArg(i32 1)
  store i32 %1, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %2 = icmp slt i32 %i1, 0
  br i1 %2, label %then, label %else

then:                                             ; preds = %entry
  %3 = sub nsw i32 0, 1
  store i32 %3, ptr %result, align 4
  br label %if-cont7

else:                                             ; preds = %entry
  br i1 true, label %then2, label %if-cont7

then2:                                            ; preds = %else
  %i3 = load i32, ptr %i, align 4
  %4 = icmp sgt i32 %i3, 0
  br i1 %4, label %then4, label %else5

then4:                                            ; preds = %then2
  store i32 1, ptr %result, align 4
  br label %if-cont

else5:                                            ; preds = %then2
  br i1 true, label %then6, label %if-cont

then6:                                            ; preds = %else5
  store i32 0, ptr %result, align 4
  br label %if-cont

if-cont:                                          ; preds = %then6, %else5, %then4
  br label %if-cont7

if-cont7:                                         ; preds = %if-cont, %else, %then
  %result8 = load i32, ptr %result, align 4
  %5 = call ptr @malloc(i32 4)
  store i32 %result8, ptr %5, align 4
  %6 = load ptr, ptr %c, align 8
  %7 = call %Unit @_WriteChannel(ptr %6, ptr %5)
  ret %Unit zeroinitializer
}

declare i32 @getIntArg(i32)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
