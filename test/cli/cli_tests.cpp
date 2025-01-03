
#include <catch2/catch_test_macros.hpp>
#include "Compile.h"
// TODO: Note: this doesn't compile all bsl functions due to them being templated. 
// Ensure we have coverage on the standard library!

TEST_CASE("BSL - Compile 1", "[cli]")
{
    auto getVI = [](std::string path, std::vector<std::string> steps){
        return new VirtualInput(
            new antlr4::ANTLRInputStream(*(new std::fstream(path))),
            steps
        );
    };

    /*
    std::vector<std::pair<std::string, std::vector<std::string>>> bslFiles; 
    bslFiles.push_back({"./bsl/lib/Types.bismuth", {"bsl", "lib", "Types"}});
    bslFiles.push_back({"./bsl/lib/Lists.bismuth", {"bsl", "lib", "Lists"}});
    bslFiles.push_back({"./bsl/lib/Optional.bismuth", {"bsl", "lib", "Optional"}});
    bslFiles.push_back({"./bsl/lib/Arrays.bismuth", {"bsl", "lib", "Arrays"}});

    std::vector<VirtualInput *> inputs; 

    for(auto i : bslFiles)
    {
        inputs.push_back(new VirtualInput(
            new antlr4::ANTLRInputStream(*(new std::fstream(i.first))),
            i.second
        ));
    }
    */


    VirtualInput * bsl_lib_types = getVI(std::string(SOURCE_DIR) + "bsl/lib/Types.bismuth", {"bsl", "lib", "Types"});
    VirtualInput * bsl_lib_lists = getVI(std::string(SOURCE_DIR) + "bsl/lib/Lists.bismuth", {"bsl", "lib", "Lists"});
    VirtualInput * bsl_lib_optional = getVI(std::string(SOURCE_DIR) + "bsl/lib/Optional.bismuth", {"bsl", "lib", "Optional"});
    VirtualInput * bsl_lib_arrays = getVI(std::string(SOURCE_DIR) + "bsl/lib/Arrays.bismuth", {"bsl", "lib", "Arrays"});

    VirtualInput * temp = new VirtualInput(
        new antlr4::ANTLRInputStream(R""""(
import bsl::lib::Types::Empty; 
import bsl::lib::Optional::Optional; 
import bsl::lib::Lists::LinkedList; 
import bsl::lib::Arrays::forEach; 

extern func printf(str s, ...);


define func linkedListToDyn<T>(LinkedList<T> list) : T[] {
    T[] ans; 

    int len := 0; 
    var ptr := Box<LinkedList<T>>::init(list); 
    var shouldLoop := true; 

    while(shouldLoop) {
        LinkedList<T> lst := *ptr; 
        ans[len] := lst.value; 
        match lst.next 
            |   Box<LinkedList<T>> nxt => {
                    ptr := nxt; 
                    len := len + 1; 
                }
            |   Empty e => {
                    shouldLoop := false; 
                }
    }

    return ans; 
}

define program :: c : Channel<-int> {
    LinkedList<int> a := LinkedList<int>::init(
        Box<LinkedList<int>>::init(LinkedList<int>::init(
            Empty::init(), 
            2
        )),
        1
    );
    
    int[] b := linkedListToDyn<int>(a);

    forEach<int>(
        b, 
        (int i) : Unit {
            printf("%u, ", i);
            return; 
        }
    );

    c.send(0); 
}

        )""""), 
        {"temp"}
    );

    std::vector<CompilerInput *> inputs; 
    inputs.push_back(bsl_lib_types);
    inputs.push_back(bsl_lib_lists);
    inputs.push_back(bsl_lib_optional);
    inputs.push_back(bsl_lib_arrays);
    inputs.push_back(temp);

    compile(
        inputs, 
        "-.ll", 
        false,
        true, 
        DisplayMode::C_STYLE,
        false, 
        false, 
        CompileType::none
    );


    REQUIRE(bsl_lib_types->getIrStr() == 
R"(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"
)");

    REQUIRE(bsl_lib_lists->getIrStr() == 
R"(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"
)");

    REQUIRE(bsl_lib_optional->getIrStr() ==
R"(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"
)");

    REQUIRE(bsl_lib_arrays->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"int[]" = type { ptr, i32, i32 }
%"(Unit + int)" = type { i32, [4 x i8] }

define %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %0, ptr %1) {
entry:
  %t = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %i = alloca i32, align 4
  %fn = alloca ptr, align 8
  %array = alloca %"int[]", align 8
  store %"int[]" %0, ptr %array, align 8
  store ptr %1, ptr %fn, align 8
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %5 = getelementptr %"int[]", ptr %array, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  %7 = icmp slt i32 %i1, %6
  br i1 %7, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, ptr %i, align 4
  %8 = getelementptr %"int[]", ptr %array, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  %10 = icmp slt i32 %i2, %9
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %11 = icmp sge i32 %i2, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr %"int[]", ptr %array, i32 0, i32 0
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr i32, ptr %13, i32 %i2
  %15 = load i32, ptr %14, align 4
  %16 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 1
  store i32 %15, ptr %17, align 4
  %18 = load %"(Unit + int)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %19 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  store %"(Unit + int)" %arrayAccess, ptr %2, align 4
  %22 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  switch i32 %23, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %25 = load %Unit, ptr %24, align 1
  store %Unit %25, ptr %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
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
  %30 = getelementptr %"int[]", ptr %array, i32 0, i32 1
  %31 = load i32, ptr %30, align 4
  %32 = icmp slt i32 %i6, %31
  br i1 %32, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}
)""");

    REQUIRE(temp->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"int[]" = type { ptr, i32, i32 }
%"bsl::lib::Lists::LinkedList<int>" = type { %"(Box<LinkedList<int>> + Empty)", i32 }
%"(Box<LinkedList<int>> + Empty)" = type { i32, [8 x i8] }
%"bsl::lib::Types::Empty" = type {}

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1

define %Unit @program(ptr %0) {
entry:
  %b = alloca %"int[]", align 8
  %a = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %1 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %2 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %3 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %4 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %5 = alloca %"bsl::lib::Types::Empty", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %6 = load %"bsl::lib::Types::Empty", ptr %5, align 1
  %7 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %3, i32 0, i32 0
  store i32 2, ptr %7, align 4
  %8 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %3, i32 0, i32 1
  store %"bsl::lib::Types::Empty" %6, ptr %8, align 1
  %9 = load %"(Box<LinkedList<int>> + Empty)", ptr %3, align 4
  %10 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %4, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %9, ptr %10, align 4
  %11 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %4, i32 0, i32 1
  store i32 2, ptr %11, align 4
  %12 = load %"bsl::lib::Lists::LinkedList<int>", ptr %4, align 4
  %13 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %12, ptr %13, align 4
  %14 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 0
  store i32 1, ptr %14, align 4
  %15 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 1
  store ptr %13, ptr %15, align 8
  %16 = load %"(Box<LinkedList<int>> + Empty)", ptr %1, align 4
  %17 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %2, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %16, ptr %17, align 4
  %18 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %2, i32 0, i32 1
  store i32 1, ptr %18, align 4
  %19 = load %"bsl::lib::Lists::LinkedList<int>", ptr %2, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %19, ptr %a, align 4
  %a1 = load %"bsl::lib::Lists::LinkedList<int>", ptr %a, align 4
  %20 = call %"int[]" @"temp::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %a1)
  store %"int[]" %20, ptr %b, align 8
  %b2 = load %"int[]", ptr %b, align 8
  %21 = call %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %b2, ptr @"program::#lambda")
  %22 = call ptr @malloc(i32 4)
  store i32 0, ptr %22, align 4
  %23 = load ptr, ptr %c, align 8
  %24 = call %Unit @_WriteChannel(ptr %23, ptr %22)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

define %"int[]" @"temp::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %0) {
entry:
  %e = alloca %"bsl::lib::Types::Empty", align 8
  %nxt = alloca ptr, align 8
  %1 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %2 = alloca i32, align 4
  %lst = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %shouldLoop = alloca i1, align 1
  %ptr = alloca ptr, align 8
  %len = alloca i32, align 4
  %ans = alloca %"int[]", align 8
  %list = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  store %"bsl::lib::Lists::LinkedList<int>" %0, ptr %list, align 4
  %3 = sext i32 2 to i64
  %4 = mul nsw i64 %3, 4
  %5 = call ptr @GC_malloc(i64 %4)
  %6 = getelementptr %"int[]", ptr %ans, i32 0, i32 0
  store ptr %5, ptr %6, align 8
  %7 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  store i32 1, ptr %7, align 4
  %8 = getelementptr %"int[]", ptr %ans, i32 0, i32 2
  store i32 2, ptr %8, align 4
  store i32 0, ptr %len, align 4
  %list1 = load %"bsl::lib::Lists::LinkedList<int>", ptr %list, align 4
  %9 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %list1, ptr %9, align 4
  store ptr %9, ptr %ptr, align 8
  store i1 true, ptr %shouldLoop, align 1
  %shouldLoop2 = load i1, ptr %shouldLoop, align 1
  br i1 %shouldLoop2, label %loop, label %rest13

loop:                                             ; preds = %match-cont, %entry
  %ptr3 = load ptr, ptr %ptr, align 8
  %10 = load %"bsl::lib::Lists::LinkedList<int>", ptr %ptr3, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %10, ptr %lst, align 4
  %len4 = load i32, ptr %len, align 4
  %11 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  %12 = load i32, ptr %11, align 4
  %13 = icmp sle i32 %12, %len4
  br i1 %13, label %then, label %else9

then:                                             ; preds = %loop
  %14 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  %15 = load i32, ptr %14, align 4
  %16 = icmp sle i32 %15, %len4
  br i1 %16, label %then5, label %else8

then5:                                            ; preds = %then
  %17 = mul nsw i32 %len4, 2
  %18 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  %19 = load i32, ptr %18, align 4
  %20 = icmp sge i32 %17, %19
  br i1 %20, label %then6, label %else

then6:                                            ; preds = %then5
  %21 = getelementptr %"int[]", ptr %ans, i32 0, i32 0
  %22 = load ptr, ptr %21, align 8
  %23 = sext i32 %17 to i64
  %24 = mul nsw i64 %23, 4
  %25 = call ptr @GC_malloc(i64 %24)
  store i32 0, ptr %2, align 4
  %26 = load i32, ptr %2, align 4
  %27 = icmp slt i32 %26, %19
  br i1 %27, label %loop7, label %rest

loop7:                                            ; preds = %loop7, %then6
  %28 = load i32, ptr %2, align 4
  %29 = getelementptr i32, ptr %22, i32 %28
  %30 = load i32, ptr %29, align 4
  %31 = getelementptr ptr, ptr %25, i32 %28
  store i32 %30, ptr %31, align 4
  %32 = add nsw i32 %28, 1
  store i32 %32, ptr %2, align 4
  %33 = load i32, ptr %2, align 4
  %34 = icmp slt i32 %33, %19
  br i1 %34, label %loop7, label %rest

rest:                                             ; preds = %loop7, %then6
  store ptr %25, ptr %21, align 8
  %35 = getelementptr %"int[]", ptr %ans, i32 0, i32 2
  store i32 %17, ptr %35, align 4
  br label %else

else:                                             ; preds = %rest, %then5
  br label %else8

else8:                                            ; preds = %else, %then
  %36 = add nsw i32 %len4, 1
  store i32 %36, ptr %11, align 4
  br label %else9

else9:                                            ; preds = %else8, %loop
  %37 = getelementptr %"int[]", ptr %ans, i32 0, i32 0
  %38 = load ptr, ptr %37, align 8
  %39 = getelementptr i32, ptr %38, i32 %len4
  %40 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %lst, i32 0, i32 1
  %41 = load i32, ptr %40, align 4
  store i32 %41, ptr %39, align 4
  %42 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %lst, i32 0, i32 0
  %43 = load %"(Box<LinkedList<int>> + Empty)", ptr %42, align 4
  store %"(Box<LinkedList<int>> + Empty)" %43, ptr %1, align 4
  %44 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  switch i32 %45, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %else9
  %46 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 1
  %47 = load ptr, ptr %46, align 8
  store ptr %47, ptr %nxt, align 8
  %nxt10 = load ptr, ptr %nxt, align 8
  store ptr %nxt10, ptr %ptr, align 8
  %len11 = load i32, ptr %len, align 4
  %48 = add nsw i32 %len11, 1
  store i32 %48, ptr %len, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %else9
  %49 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 1
  %50 = load %"bsl::lib::Types::Empty", ptr %49, align 1
  store %"bsl::lib::Types::Empty" %50, ptr %e, align 1
  store i1 false, ptr %shouldLoop, align 1
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %else9
  %shouldLoop12 = load i1, ptr %shouldLoop, align 1
  br i1 %shouldLoop12, label %loop, label %rest13

rest13:                                           ; preds = %match-cont, %entry
  %ans14 = load %"int[]", ptr %ans, align 8
  ret %"int[]" %ans14
}

declare ptr @GC_malloc(i64)

define private %Unit @"program::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call %Unit (ptr, ...) @printf(ptr @0, i32 %i1)
  ret %Unit zeroinitializer
}

declare %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]", ptr)

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
)""");
}




TEST_CASE("BSL - Compile 3", "[cli]")
{
    auto getVI = [](std::string path, std::vector<std::string> steps){
        return new VirtualInput(
            new antlr4::ANTLRInputStream(*(new std::fstream(path))),
            steps
        );
    };

    /*
    std::vector<std::pair<std::string, std::vector<std::string>>> bslFiles; 
    bslFiles.push_back({"./bsl/lib/Types.bismuth", {"bsl", "lib", "Types"}});
    bslFiles.push_back({"./bsl/lib/Lists.bismuth", {"bsl", "lib", "Lists"}});
    bslFiles.push_back({"./bsl/lib/Optional.bismuth", {"bsl", "lib", "Optional"}});
    bslFiles.push_back({"./bsl/lib/Arrays.bismuth", {"bsl", "lib", "Arrays"}});

    std::vector<VirtualInput *> inputs; 

    for(auto i : bslFiles)
    {
        inputs.push_back(new VirtualInput(
            new antlr4::ANTLRInputStream(*(new std::fstream(i.first))),
            i.second
        ));
    }
    */


    VirtualInput * bsl_lib_types = getVI(std::string(SOURCE_DIR) + "bsl/lib/Types.bismuth", {"bsl", "lib", "Types"});
    VirtualInput * bsl_lib_lists = getVI(std::string(SOURCE_DIR) + "bsl/lib/Lists.bismuth", {"bsl", "lib", "Lists"});
    VirtualInput * bsl_lib_optional = getVI(std::string(SOURCE_DIR) + "bsl/lib/Optional.bismuth", {"bsl", "lib", "Optional"});
    VirtualInput * bsl_lib_arrays = getVI(std::string(SOURCE_DIR) + "bsl/lib/Arrays.bismuth", {"bsl", "lib", "Arrays"});

    VirtualInput * temp = new VirtualInput(
        new antlr4::ANTLRInputStream(R""""(
import bsl::lib::Types::Empty; 
import bsl::lib::Optional::Optional; 
import bsl::lib::Lists::LinkedList; 
import bsl::lib::Arrays::forEach; 

import bsl::lib::Lists::map as llMap; 

extern func printf(str s, ...);

define func linkedListToDyn<T>(LinkedList<T> list) : T[] {
    T[] ans; 

    int len := 0; 
    var ptr := Box<LinkedList<T>>::init(list); 

    while(true) {
        LinkedList<T> lst := *ptr; 
        ans[len] := lst.value; 
        match lst.next
            |   Box<LinkedList<T>> nxt => {
                    ptr := nxt; 
                    len := len + 1; 
                }
            |   Empty e => return ans; 
    }

    return ans; 
}

define program :: c : Channel<-int> {
    LinkedList<int> a := LinkedList<int>::init(
        Box<LinkedList<int>>::init(LinkedList<int>::init(
            Empty::init(), 
            2
        )),
        1
    );
    

    int[] b := linkedListToDyn<int>(a);

    forEach<int>(
        b, 
        (int i) : Unit {
            printf("%u, ", i);
            return; 
        }
    );

    printf("\n");

    LinkedList<int> mapped := llMap<int, int>(
        a, 
        (int val, int idx) : int {
            # printf("CALLED %u, %u\n", val, idx);
            return (val + 1) * (idx + 1); 
        }
    );

    forEach<int>(
        linkedListToDyn<int>(mapped),
        (int i) : Unit {
            printf("%u, ", i);
            return; 
        }
    );

    printf("\n");

    c.send(0); 
}
        )""""), 
        {"temp3"}
    );

    std::vector<CompilerInput *> inputs; 
    inputs.push_back(bsl_lib_types);
    inputs.push_back(bsl_lib_lists);
    inputs.push_back(bsl_lib_optional);
    inputs.push_back(bsl_lib_arrays);
    inputs.push_back(temp);

    compile(
        inputs, 
        "-.ll", 
        false,
        true, 
        DisplayMode::C_STYLE,
        false, 
        false, 
        CompileType::none
    );


    REQUIRE(bsl_lib_types->getIrStr() == 
R"(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"
)");

    REQUIRE(bsl_lib_lists->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%"bsl::lib::Lists::LinkedList<int>" = type { %"(Box<LinkedList<int>> + Empty)", i32 }
%"(Box<LinkedList<int>> + Empty)" = type { i32, [8 x i8] }
%"(int -> int + int, int -> int)" = type { i32, [8 x i8] }
%"bsl::lib::Types::Empty" = type {}

define %"bsl::lib::Lists::LinkedList<int>" @"bsl::lib::Lists::map<int, int>"(%"bsl::lib::Lists::LinkedList<int>" %0, %"(int -> int + int, int -> int)" %1) {
entry:
  %e.0 = alloca %"bsl::lib::Types::Empty", align 8
  %ele.0 = alloca ptr, align 8
  %2 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %3 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %4 = alloca %"bsl::lib::Types::Empty", align 8
  %i.0 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %nxt.0 = alloca ptr, align 8
  %5 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %shouldLoop.0 = alloca i1, align 1
  %idx = alloca i32, align 4
  %origPtr.0 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %ansConstPtr = alloca ptr, align 8
  %ansPtr.0 = alloca ptr, align 8
  %6 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %7 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %8 = alloca %"bsl::lib::Types::Empty", align 8
  %m2 = alloca ptr, align 8
  %e = alloca %"bsl::lib::Types::Empty", align 8
  %a = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %ele = alloca ptr, align 8
  %9 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %10 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %11 = alloca %"bsl::lib::Types::Empty", align 8
  %i = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %nxt = alloca ptr, align 8
  %12 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %shouldLoop = alloca i1, align 1
  %origPtr = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %ansPtr = alloca ptr, align 8
  %ans = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %13 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %14 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %15 = alloca %"bsl::lib::Types::Empty", align 8
  %m1 = alloca ptr, align 8
  %16 = alloca %"(int -> int + int, int -> int)", align 8
  %mapper = alloca %"(int -> int + int, int -> int)", align 8
  %array = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  store %"bsl::lib::Lists::LinkedList<int>" %0, ptr %array, align 4
  store %"(int -> int + int, int -> int)" %1, ptr %mapper, align 4
  %mapper1 = load %"(int -> int + int, int -> int)", ptr %mapper, align 4
  store %"(int -> int + int, int -> int)" %mapper1, ptr %16, align 4
  %17 = getelementptr %"(int -> int + int, int -> int)", ptr %16, i32 0, i32 0
  %18 = load i32, ptr %17, align 4
  switch i32 %18, label %match-cont33 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch214
  ]

tagBranch1:                                       ; preds = %entry
  %19 = getelementptr %"(int -> int + int, int -> int)", ptr %16, i32 0, i32 1
  %20 = load ptr, ptr %19, align 8
  store ptr %20, ptr %m1, align 8
  %21 = load %"bsl::lib::Types::Empty", ptr %15, align 1
  %22 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %array, i32 0, i32 1
  %23 = load i32, ptr %22, align 4
  %m12 = load ptr, ptr %m1, align 8
  %24 = call i32 %m12(i32 %23)
  %25 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %13, i32 0, i32 0
  store i32 2, ptr %25, align 4
  %26 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %13, i32 0, i32 1
  store %"bsl::lib::Types::Empty" %21, ptr %26, align 1
  %27 = load %"(Box<LinkedList<int>> + Empty)", ptr %13, align 4
  %28 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %14, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %27, ptr %28, align 4
  %29 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %14, i32 0, i32 1
  store i32 %24, ptr %29, align 4
  %30 = load %"bsl::lib::Lists::LinkedList<int>", ptr %14, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %30, ptr %ans, align 4
  %ans3 = load %"bsl::lib::Lists::LinkedList<int>", ptr %ans, align 4
  %31 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %ans3, ptr %31, align 4
  store ptr %31, ptr %ansPtr, align 8
  %32 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %array, i32 0, i32 0
  %33 = load %"(Box<LinkedList<int>> + Empty)", ptr %32, align 4
  store %"(Box<LinkedList<int>> + Empty)" %33, ptr %origPtr, align 4
  store i1 true, ptr %shouldLoop, align 1
  %shouldLoop4 = load i1, ptr %shouldLoop, align 1
  br i1 %shouldLoop4, label %loop, label %rest

loop:                                             ; preds = %match-cont, %tagBranch1
  %origPtr5 = load %"(Box<LinkedList<int>> + Empty)", ptr %origPtr, align 4
  store %"(Box<LinkedList<int>> + Empty)" %origPtr5, ptr %12, align 4
  %34 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %12, i32 0, i32 0
  %35 = load i32, ptr %34, align 4
  switch i32 %35, label %match-cont [
    i32 1, label %tagBranch16
    i32 2, label %tagBranch2
  ]

tagBranch16:                                      ; preds = %loop
  %36 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %12, i32 0, i32 1
  %37 = load ptr, ptr %36, align 8
  store ptr %37, ptr %nxt, align 8
  %nxt7 = load ptr, ptr %nxt, align 8
  %38 = load %"bsl::lib::Lists::LinkedList<int>", ptr %nxt7, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %38, ptr %i, align 4
  %39 = load %"bsl::lib::Types::Empty", ptr %11, align 1
  %40 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %i, i32 0, i32 1
  %41 = load i32, ptr %40, align 4
  %m18 = load ptr, ptr %m1, align 8
  %42 = call i32 %m18(i32 %41)
  %43 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %9, i32 0, i32 0
  store i32 2, ptr %43, align 4
  %44 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %9, i32 0, i32 1
  store %"bsl::lib::Types::Empty" %39, ptr %44, align 1
  %45 = load %"(Box<LinkedList<int>> + Empty)", ptr %9, align 4
  %46 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %10, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %45, ptr %46, align 4
  %47 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %10, i32 0, i32 1
  store i32 %42, ptr %47, align 4
  %48 = load %"bsl::lib::Lists::LinkedList<int>", ptr %10, align 4
  %49 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %48, ptr %49, align 4
  store ptr %49, ptr %ele, align 8
  %ansPtr9 = load ptr, ptr %ansPtr, align 8
  %50 = load %"bsl::lib::Lists::LinkedList<int>", ptr %ansPtr9, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %50, ptr %a, align 4
  %51 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %a, i32 0, i32 0
  %ele10 = load ptr, ptr %ele, align 8
  %52 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %51, i32 0, i32 0
  store i32 1, ptr %52, align 4
  %53 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %51, i32 0, i32 1
  store ptr %ele10, ptr %53, align 8
  %ele11 = load ptr, ptr %ele, align 8
  store ptr %ele11, ptr %ansPtr, align 8
  %54 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %i, i32 0, i32 0
  %55 = load %"(Box<LinkedList<int>> + Empty)", ptr %54, align 4
  store %"(Box<LinkedList<int>> + Empty)" %55, ptr %origPtr, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %loop
  %56 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %12, i32 0, i32 1
  %57 = load %"bsl::lib::Types::Empty", ptr %56, align 1
  store %"bsl::lib::Types::Empty" %57, ptr %e, align 1
  store i1 false, ptr %shouldLoop, align 1
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch16, %loop
  %shouldLoop12 = load i1, ptr %shouldLoop, align 1
  br i1 %shouldLoop12, label %loop, label %rest

rest:                                             ; preds = %match-cont, %tagBranch1
  %ans13 = load %"bsl::lib::Lists::LinkedList<int>", ptr %ans, align 4
  ret %"bsl::lib::Lists::LinkedList<int>" %ans13

tagBranch214:                                     ; preds = %entry
  %58 = getelementptr %"(int -> int + int, int -> int)", ptr %16, i32 0, i32 1
  %59 = load ptr, ptr %58, align 8
  store ptr %59, ptr %m2, align 8
  %60 = load %"bsl::lib::Types::Empty", ptr %8, align 1
  %61 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %array, i32 0, i32 1
  %62 = load i32, ptr %61, align 4
  %m215 = load ptr, ptr %m2, align 8
  %63 = call i32 %m215(i32 %62, i32 0)
  %64 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %6, i32 0, i32 0
  store i32 2, ptr %64, align 4
  %65 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %6, i32 0, i32 1
  store %"bsl::lib::Types::Empty" %60, ptr %65, align 1
  %66 = load %"(Box<LinkedList<int>> + Empty)", ptr %6, align 4
  %67 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %7, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %66, ptr %67, align 4
  %68 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %7, i32 0, i32 1
  store i32 %63, ptr %68, align 4
  %69 = load %"bsl::lib::Lists::LinkedList<int>", ptr %7, align 4
  %70 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %69, ptr %70, align 4
  store ptr %70, ptr %ansPtr.0, align 8
  %ansPtr.016 = load ptr, ptr %ansPtr.0, align 8
  store ptr %ansPtr.016, ptr %ansConstPtr, align 8
  %71 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %array, i32 0, i32 0
  %72 = load %"(Box<LinkedList<int>> + Empty)", ptr %71, align 4
  store %"(Box<LinkedList<int>> + Empty)" %72, ptr %origPtr.0, align 4
  store i32 1, ptr %idx, align 4
  store i1 true, ptr %shouldLoop.0, align 1
  %shouldLoop.017 = load i1, ptr %shouldLoop.0, align 1
  br i1 %shouldLoop.017, label %loop18, label %rest31

loop18:                                           ; preds = %match-cont29, %tagBranch214
  %origPtr.019 = load %"(Box<LinkedList<int>> + Empty)", ptr %origPtr.0, align 4
  store %"(Box<LinkedList<int>> + Empty)" %origPtr.019, ptr %5, align 4
  %73 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %5, i32 0, i32 0
  %74 = load i32, ptr %73, align 4
  switch i32 %74, label %match-cont29 [
    i32 1, label %tagBranch120
    i32 2, label %tagBranch228
  ]

tagBranch120:                                     ; preds = %loop18
  %75 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %5, i32 0, i32 1
  %76 = load ptr, ptr %75, align 8
  store ptr %76, ptr %nxt.0, align 8
  %nxt.021 = load ptr, ptr %nxt.0, align 8
  %77 = load %"bsl::lib::Lists::LinkedList<int>", ptr %nxt.021, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %77, ptr %i.0, align 4
  %78 = load %"bsl::lib::Types::Empty", ptr %4, align 1
  %79 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %i.0, i32 0, i32 1
  %80 = load i32, ptr %79, align 4
  %idx22 = load i32, ptr %idx, align 4
  %m223 = load ptr, ptr %m2, align 8
  %81 = call i32 %m223(i32 %80, i32 %idx22)
  %82 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %2, i32 0, i32 0
  store i32 2, ptr %82, align 4
  %83 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %2, i32 0, i32 1
  store %"bsl::lib::Types::Empty" %78, ptr %83, align 1
  %84 = load %"(Box<LinkedList<int>> + Empty)", ptr %2, align 4
  %85 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %3, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %84, ptr %85, align 4
  %86 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %3, i32 0, i32 1
  store i32 %81, ptr %86, align 4
  %87 = load %"bsl::lib::Lists::LinkedList<int>", ptr %3, align 4
  %88 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %87, ptr %88, align 4
  store ptr %88, ptr %ele.0, align 8
  %idx24 = load i32, ptr %idx, align 4
  %89 = add nsw i32 %idx24, 1
  store i32 %89, ptr %idx, align 4
  %ansPtr.025 = load ptr, ptr %ansPtr.0, align 8
  %90 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %ansPtr.025, i32 0, i32 0
  %ele.026 = load ptr, ptr %ele.0, align 8
  %91 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %90, i32 0, i32 0
  store i32 1, ptr %91, align 4
  %92 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %90, i32 0, i32 1
  store ptr %ele.026, ptr %92, align 8
  %ele.027 = load ptr, ptr %ele.0, align 8
  store ptr %ele.027, ptr %ansPtr.0, align 8
  %93 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %i.0, i32 0, i32 0
  %94 = load %"(Box<LinkedList<int>> + Empty)", ptr %93, align 4
  store %"(Box<LinkedList<int>> + Empty)" %94, ptr %origPtr.0, align 4
  br label %match-cont29

tagBranch228:                                     ; preds = %loop18
  %95 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %5, i32 0, i32 1
  %96 = load %"bsl::lib::Types::Empty", ptr %95, align 1
  store %"bsl::lib::Types::Empty" %96, ptr %e.0, align 1
  store i1 false, ptr %shouldLoop.0, align 1
  br label %match-cont29

match-cont29:                                     ; preds = %tagBranch228, %tagBranch120, %loop18
  %shouldLoop.030 = load i1, ptr %shouldLoop.0, align 1
  br i1 %shouldLoop.030, label %loop18, label %rest31

rest31:                                           ; preds = %match-cont29, %tagBranch214
  %ansConstPtr32 = load ptr, ptr %ansConstPtr, align 8
  %97 = load %"bsl::lib::Lists::LinkedList<int>", ptr %ansConstPtr32, align 4
  ret %"bsl::lib::Lists::LinkedList<int>" %97

match-cont33:                                     ; preds = %entry
  unreachable
}

declare ptr @GC_malloc(i64)
)""");

    REQUIRE(bsl_lib_optional->getIrStr() ==
R"(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"
)");

    REQUIRE(bsl_lib_arrays->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"int[]" = type { ptr, i32, i32 }
%"(Unit + int)" = type { i32, [4 x i8] }

define %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %0, ptr %1) {
entry:
  %t = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %i = alloca i32, align 4
  %fn = alloca ptr, align 8
  %array = alloca %"int[]", align 8
  store %"int[]" %0, ptr %array, align 8
  store ptr %1, ptr %fn, align 8
  store i32 0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %5 = getelementptr %"int[]", ptr %array, i32 0, i32 1
  %6 = load i32, ptr %5, align 4
  %7 = icmp slt i32 %i1, %6
  br i1 %7, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, ptr %i, align 4
  %8 = getelementptr %"int[]", ptr %array, i32 0, i32 1
  %9 = load i32, ptr %8, align 4
  %10 = icmp slt i32 %i2, %9
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %11 = icmp sge i32 %i2, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr %"int[]", ptr %array, i32 0, i32 0
  %13 = load ptr, ptr %12, align 8
  %14 = getelementptr i32, ptr %13, i32 %i2
  %15 = load i32, ptr %14, align 4
  %16 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 0
  store i32 2, ptr %16, align 4
  %17 = getelementptr %"(Unit + int)", ptr %4, i32 0, i32 1
  store i32 %15, ptr %17, align 4
  %18 = load %"(Unit + int)", ptr %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %19 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 0
  store i32 1, ptr %19, align 4
  %20 = getelementptr %"(Unit + int)", ptr %3, i32 0, i32 1
  store %Unit zeroinitializer, ptr %20, align 1
  %21 = load %"(Unit + int)", ptr %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %18, %accessGTZ ], [ %21, %accessBad ]
  store %"(Unit + int)" %arrayAccess, ptr %2, align 4
  %22 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 0
  %23 = load i32, ptr %22, align 4
  switch i32 %23, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %24 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
  %25 = load %Unit, ptr %24, align 1
  store %Unit %25, ptr %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + int)", ptr %2, i32 0, i32 1
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
  %30 = getelementptr %"int[]", ptr %array, i32 0, i32 1
  %31 = load i32, ptr %30, align 4
  %32 = icmp slt i32 %i6, %31
  br i1 %32, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}
)""");

    REQUIRE(temp->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"bsl::lib::Lists::LinkedList<int>" = type { %"(Box<LinkedList<int>> + Empty)", i32 }
%"(Box<LinkedList<int>> + Empty)" = type { i32, [8 x i8] }
%"(int -> int + int, int -> int)" = type { i32, [8 x i8] }
%"int[]" = type { ptr, i32, i32 }
%"bsl::lib::Types::Empty" = type {}

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define %Unit @program(ptr %0) {
entry:
  %mapped = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %1 = alloca %"(int -> int + int, int -> int)", align 8
  %b = alloca %"int[]", align 8
  %a = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %2 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %3 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %4 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %5 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %6 = alloca %"bsl::lib::Types::Empty", align 8
  %c = alloca ptr, align 8
  store ptr %0, ptr %c, align 8
  %7 = load %"bsl::lib::Types::Empty", ptr %6, align 1
  %8 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %4, i32 0, i32 0
  store i32 2, ptr %8, align 4
  %9 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %4, i32 0, i32 1
  store %"bsl::lib::Types::Empty" %7, ptr %9, align 1
  %10 = load %"(Box<LinkedList<int>> + Empty)", ptr %4, align 4
  %11 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %5, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %10, ptr %11, align 4
  %12 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %5, i32 0, i32 1
  store i32 2, ptr %12, align 4
  %13 = load %"bsl::lib::Lists::LinkedList<int>", ptr %5, align 4
  %14 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %13, ptr %14, align 4
  %15 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %2, i32 0, i32 0
  store i32 1, ptr %15, align 4
  %16 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %2, i32 0, i32 1
  store ptr %14, ptr %16, align 8
  %17 = load %"(Box<LinkedList<int>> + Empty)", ptr %2, align 4
  %18 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %3, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %17, ptr %18, align 4
  %19 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %3, i32 0, i32 1
  store i32 1, ptr %19, align 4
  %20 = load %"bsl::lib::Lists::LinkedList<int>", ptr %3, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %20, ptr %a, align 4
  %a1 = load %"bsl::lib::Lists::LinkedList<int>", ptr %a, align 4
  %21 = call %"int[]" @"temp3::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %a1)
  store %"int[]" %21, ptr %b, align 8
  %b2 = load %"int[]", ptr %b, align 8
  %22 = call %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %b2, ptr @"program::#lambda")
  %23 = call %Unit (ptr, ...) @printf(ptr @1)
  %a3 = load %"bsl::lib::Lists::LinkedList<int>", ptr %a, align 4
  %24 = getelementptr %"(int -> int + int, int -> int)", ptr %1, i32 0, i32 0
  store i32 2, ptr %24, align 4
  %25 = getelementptr %"(int -> int + int, int -> int)", ptr %1, i32 0, i32 1
  store ptr @"program::#lambda.0", ptr %25, align 8
  %26 = load %"(int -> int + int, int -> int)", ptr %1, align 4
  %27 = call %"bsl::lib::Lists::LinkedList<int>" @"bsl::lib::Lists::map<int, int>"(%"bsl::lib::Lists::LinkedList<int>" %a3, %"(int -> int + int, int -> int)" %26)
  store %"bsl::lib::Lists::LinkedList<int>" %27, ptr %mapped, align 4
  %mapped4 = load %"bsl::lib::Lists::LinkedList<int>", ptr %mapped, align 4
  %28 = call %"int[]" @"temp3::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %mapped4)
  %29 = call %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %28, ptr @"program::#lambda.1")
  %30 = call %Unit (ptr, ...) @printf(ptr @3)
  %31 = call ptr @malloc(i32 4)
  store i32 0, ptr %31, align 4
  %32 = load ptr, ptr %c, align 8
  %33 = call %Unit @_WriteChannel(ptr %32, ptr %31)
  ret %Unit zeroinitializer
}

declare %Unit @printf(ptr, ...)

define %"int[]" @"temp3::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %0) {
entry:
  %e = alloca %"bsl::lib::Types::Empty", align 8
  %nxt = alloca ptr, align 8
  %1 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %2 = alloca i32, align 4
  %lst = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %ptr = alloca ptr, align 8
  %len = alloca i32, align 4
  %ans = alloca %"int[]", align 8
  %list = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  store %"bsl::lib::Lists::LinkedList<int>" %0, ptr %list, align 4
  %3 = sext i32 2 to i64
  %4 = mul nsw i64 %3, 4
  %5 = call ptr @GC_malloc(i64 %4)
  %6 = getelementptr %"int[]", ptr %ans, i32 0, i32 0
  store ptr %5, ptr %6, align 8
  %7 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  store i32 1, ptr %7, align 4
  %8 = getelementptr %"int[]", ptr %ans, i32 0, i32 2
  store i32 2, ptr %8, align 4
  store i32 0, ptr %len, align 4
  %list1 = load %"bsl::lib::Lists::LinkedList<int>", ptr %list, align 4
  %9 = call ptr @GC_malloc(i64 16)
  store %"bsl::lib::Lists::LinkedList<int>" %list1, ptr %9, align 4
  store ptr %9, ptr %ptr, align 8
  br i1 true, label %loop, label %rest12

loop:                                             ; preds = %match-cont, %entry
  %ptr2 = load ptr, ptr %ptr, align 8
  %10 = load %"bsl::lib::Lists::LinkedList<int>", ptr %ptr2, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %10, ptr %lst, align 4
  %len3 = load i32, ptr %len, align 4
  %11 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  %12 = load i32, ptr %11, align 4
  %13 = icmp sle i32 %12, %len3
  br i1 %13, label %then, label %else8

then:                                             ; preds = %loop
  %14 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  %15 = load i32, ptr %14, align 4
  %16 = icmp sle i32 %15, %len3
  br i1 %16, label %then4, label %else7

then4:                                            ; preds = %then
  %17 = mul nsw i32 %len3, 2
  %18 = getelementptr %"int[]", ptr %ans, i32 0, i32 1
  %19 = load i32, ptr %18, align 4
  %20 = icmp sge i32 %17, %19
  br i1 %20, label %then5, label %else

then5:                                            ; preds = %then4
  %21 = getelementptr %"int[]", ptr %ans, i32 0, i32 0
  %22 = load ptr, ptr %21, align 8
  %23 = sext i32 %17 to i64
  %24 = mul nsw i64 %23, 4
  %25 = call ptr @GC_malloc(i64 %24)
  store i32 0, ptr %2, align 4
  %26 = load i32, ptr %2, align 4
  %27 = icmp slt i32 %26, %19
  br i1 %27, label %loop6, label %rest

loop6:                                            ; preds = %loop6, %then5
  %28 = load i32, ptr %2, align 4
  %29 = getelementptr i32, ptr %22, i32 %28
  %30 = load i32, ptr %29, align 4
  %31 = getelementptr ptr, ptr %25, i32 %28
  store i32 %30, ptr %31, align 4
  %32 = add nsw i32 %28, 1
  store i32 %32, ptr %2, align 4
  %33 = load i32, ptr %2, align 4
  %34 = icmp slt i32 %33, %19
  br i1 %34, label %loop6, label %rest

rest:                                             ; preds = %loop6, %then5
  store ptr %25, ptr %21, align 8
  %35 = getelementptr %"int[]", ptr %ans, i32 0, i32 2
  store i32 %17, ptr %35, align 4
  br label %else

else:                                             ; preds = %rest, %then4
  br label %else7

else7:                                            ; preds = %else, %then
  %36 = add nsw i32 %len3, 1
  store i32 %36, ptr %11, align 4
  br label %else8

else8:                                            ; preds = %else7, %loop
  %37 = getelementptr %"int[]", ptr %ans, i32 0, i32 0
  %38 = load ptr, ptr %37, align 8
  %39 = getelementptr i32, ptr %38, i32 %len3
  %40 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %lst, i32 0, i32 1
  %41 = load i32, ptr %40, align 4
  store i32 %41, ptr %39, align 4
  %42 = getelementptr %"bsl::lib::Lists::LinkedList<int>", ptr %lst, i32 0, i32 0
  %43 = load %"(Box<LinkedList<int>> + Empty)", ptr %42, align 4
  store %"(Box<LinkedList<int>> + Empty)" %43, ptr %1, align 4
  %44 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 0
  %45 = load i32, ptr %44, align 4
  switch i32 %45, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %else8
  %46 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 1
  %47 = load ptr, ptr %46, align 8
  store ptr %47, ptr %nxt, align 8
  %nxt9 = load ptr, ptr %nxt, align 8
  store ptr %nxt9, ptr %ptr, align 8
  %len10 = load i32, ptr %len, align 4
  %48 = add nsw i32 %len10, 1
  store i32 %48, ptr %len, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %else8
  %49 = getelementptr %"(Box<LinkedList<int>> + Empty)", ptr %1, i32 0, i32 1
  %50 = load %"bsl::lib::Types::Empty", ptr %49, align 1
  store %"bsl::lib::Types::Empty" %50, ptr %e, align 1
  %ans11 = load %"int[]", ptr %ans, align 8
  ret %"int[]" %ans11

match-cont:                                       ; preds = %tagBranch1, %else8
  br i1 true, label %loop, label %rest12

rest12:                                           ; preds = %match-cont, %entry
  %ans13 = load %"int[]", ptr %ans, align 8
  ret %"int[]" %ans13
}

declare ptr @GC_malloc(i64)

define private %Unit @"program::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call %Unit (ptr, ...) @printf(ptr @0, i32 %i1)
  ret %Unit zeroinitializer
}

declare %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]", ptr)

define private i32 @"program::#lambda.0"(i32 %0, i32 %1) {
entry:
  %idx = alloca i32, align 4
  %val = alloca i32, align 4
  store i32 %0, ptr %val, align 4
  store i32 %1, ptr %idx, align 4
  %val1 = load i32, ptr %val, align 4
  %2 = add nsw i32 %val1, 1
  %idx2 = load i32, ptr %idx, align 4
  %3 = add nsw i32 %idx2, 1
  %4 = mul nsw i32 %2, %3
  ret i32 %4
}

declare %"bsl::lib::Lists::LinkedList<int>" @"bsl::lib::Lists::map<int, int>"(%"bsl::lib::Lists::LinkedList<int>", %"(int -> int + int, int -> int)")

define private %Unit @"program::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, ptr %i, align 4
  %i1 = load i32, ptr %i, align 4
  %1 = call %Unit (ptr, ...) @printf(ptr @2, i32 %i1)
  ret %Unit zeroinitializer
}

declare ptr @malloc(i32)

declare %Unit @_WriteChannel(ptr, ptr)
)""");
}
