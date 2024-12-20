
#include <catch2/catch_test_macros.hpp>
#include "Compile.h"
#include <filesystem>
// TODO: Note: this doesn't compile all bsl functions due to them being templated. 
// Ensure we have coverage on the standard library!

TEST_CASE("BSL - Compile 1", "[cli]")
{
  std::cout << std::filesystem::current_path() << std::endl;
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


    VirtualInput * bsl_lib_types = getVI("../../bsl/lib/Types.bismuth", {"bsl", "lib", "Types"});
    VirtualInput * bsl_lib_lists = getVI("../../bsl/lib/Lists.bismuth", {"bsl", "lib", "Lists"});
    VirtualInput * bsl_lib_optional = getVI("../../bsl/lib/Optional.bismuth", {"bsl", "lib", "Optional"});
    VirtualInput * bsl_lib_arrays = getVI("../../bsl/lib/Arrays.bismuth", {"bsl", "lib", "Arrays"});

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
%"int[]" = type { i32*, i32, i32 }
%"(Unit + int)" = type { i32, [4 x i8] }

define %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %0, %Unit (i32)* %1) {
entry:
  %t = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %i = alloca i32, align 4
  %fn = alloca %Unit (i32)*, align 8
  %array = alloca %"int[]", align 8
  store %"int[]" %0, %"int[]"* %array, align 8
  store %Unit (i32)* %1, %Unit (i32)** %fn, align 8
  store i32 0, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %5 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 1
  %6 = load i32, i32* %5, align 4
  %7 = icmp slt i32 %i1, %6
  br i1 %7, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, i32* %i, align 4
  %8 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 1
  %9 = load i32, i32* %8, align 4
  %10 = icmp slt i32 %i2, %9
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %11 = icmp sge i32 %i2, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 0
  %13 = load i32*, i32** %12, align 8
  %14 = getelementptr i32, i32* %13, i32 %i2
  %15 = load i32, i32* %14, align 4
  %16 = getelementptr %"(Unit + int)", %"(Unit + int)"* %4, i32 0, i32 0
  store i32 2, i32* %16, align 4
  %17 = getelementptr %"(Unit + int)", %"(Unit + int)"* %4, i32 0, i32 1
  %18 = bitcast [4 x i8]* %17 to i32*
  store i32 %15, i32* %18, align 4
  %19 = load %"(Unit + int)", %"(Unit + int)"* %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %20 = getelementptr %"(Unit + int)", %"(Unit + int)"* %3, i32 0, i32 0
  store i32 1, i32* %20, align 4
  %21 = getelementptr %"(Unit + int)", %"(Unit + int)"* %3, i32 0, i32 1
  %22 = bitcast [4 x i8]* %21 to %Unit*
  store %Unit zeroinitializer, %Unit* %22, align 1
  %23 = load %"(Unit + int)", %"(Unit + int)"* %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %19, %accessGTZ ], [ %23, %accessBad ]
  store %"(Unit + int)" %arrayAccess, %"(Unit + int)"* %2, align 4
  %24 = getelementptr %"(Unit + int)", %"(Unit + int)"* %2, i32 0, i32 0
  %25 = load i32, i32* %24, align 4
  switch i32 %25, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + int)", %"(Unit + int)"* %2, i32 0, i32 1
  %27 = bitcast [4 x i8]* %26 to %Unit*
  %28 = load %Unit, %Unit* %27, align 1
  store %Unit %28, %Unit* %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %29 = getelementptr %"(Unit + int)", %"(Unit + int)"* %2, i32 0, i32 1
  %30 = bitcast [4 x i8]* %29 to i32*
  %31 = load i32, i32* %30, align 4
  store i32 %31, i32* %t, align 4
  %t3 = load i32, i32* %t, align 4
  %fn4 = load %Unit (i32)*, %Unit (i32)** %fn, align 8
  %32 = call %Unit %fn4(i32 %t3)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i5 = load i32, i32* %i, align 4
  %33 = add nsw i32 %i5, 1
  store i32 %33, i32* %i, align 4
  %i6 = load i32, i32* %i, align 4
  %34 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 1
  %35 = load i32, i32* %34, align 4
  %36 = icmp slt i32 %i6, %35
  br i1 %36, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}
)""");

    REQUIRE(temp->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%_Channel = type opaque
%"int[]" = type { i32*, i32, i32 }
%"bsl::lib::Lists::LinkedList<int>" = type { %"(Box<LinkedList<int>> + Empty)", i32 }
%"(Box<LinkedList<int>> + Empty)" = type { i32, [8 x i8] }
%"bsl::lib::Types::Empty" = type {}

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1

define %Unit @program(%_Channel* %0) {
entry:
  %b = alloca %"int[]", align 8
  %a = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %1 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %2 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %3 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %4 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %5 = alloca %"bsl::lib::Types::Empty", align 8
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %6 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %5, align 1
  %7 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %3, i32 0, i32 0
  store i32 2, i32* %7, align 4
  %8 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %3, i32 0, i32 1
  %9 = bitcast [8 x i8]* %8 to %"bsl::lib::Types::Empty"*
  store %"bsl::lib::Types::Empty" %6, %"bsl::lib::Types::Empty"* %9, align 1
  %10 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %3, align 4
  %11 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %4, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %10, %"(Box<LinkedList<int>> + Empty)"* %11, align 4
  %12 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %4, i32 0, i32 1
  store i32 2, i32* %12, align 4
  %13 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %4, align 4
  %14 = call i8* @GC_malloc(i64 16)
  %15 = bitcast i8* %14 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %13, %"bsl::lib::Lists::LinkedList<int>"* %15, align 4
  %16 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 0
  store i32 1, i32* %16, align 4
  %17 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 1
  %18 = bitcast [8 x i8]* %17 to %"bsl::lib::Lists::LinkedList<int>"**
  store %"bsl::lib::Lists::LinkedList<int>"* %15, %"bsl::lib::Lists::LinkedList<int>"** %18, align 8
  %19 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, align 4
  %20 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %2, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %19, %"(Box<LinkedList<int>> + Empty)"* %20, align 4
  %21 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %2, i32 0, i32 1
  store i32 1, i32* %21, align 4
  %22 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %2, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %22, %"bsl::lib::Lists::LinkedList<int>"* %a, align 4
  %a1 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %a, align 4
  %23 = call %"int[]" @"temp::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %a1)
  store %"int[]" %23, %"int[]"* %b, align 8
  %b2 = load %"int[]", %"int[]"* %b, align 8
  %24 = call %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %b2, %Unit (i32)* @"program::#lambda")
  %25 = call i8* @malloc(i32 4)
  %26 = bitcast i8* %25 to i32*
  store i32 0, i32* %26, align 4
  %27 = load %_Channel*, %_Channel** %c, align 8
  %28 = call %Unit @_WriteChannel(%_Channel* %27, i8* %25)
  ret %Unit zeroinitializer
}

declare %Unit @printf(i8*, ...)

define %"int[]" @"temp::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %0) {
entry:
  %e = alloca %"bsl::lib::Types::Empty", align 8
  %nxt = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %1 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %2 = alloca i32, align 4
  %lst = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %shouldLoop = alloca i1, align 1
  %ptr = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %len = alloca i32, align 4
  %ans = alloca %"int[]", align 8
  %list = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  store %"bsl::lib::Lists::LinkedList<int>" %0, %"bsl::lib::Lists::LinkedList<int>"* %list, align 4
  %3 = sext i32 2 to i64
  %4 = mul nsw i64 %3, 4
  %5 = call i8* @GC_malloc(i64 %4)
  %6 = bitcast i8* %5 to i32*
  %7 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 0
  store i32* %6, i32** %7, align 8
  %8 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  store i32 1, i32* %8, align 4
  %9 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 2
  store i32 2, i32* %9, align 4
  store i32 0, i32* %len, align 4
  %list1 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %list, align 4
  %10 = call i8* @GC_malloc(i64 16)
  %11 = bitcast i8* %10 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %list1, %"bsl::lib::Lists::LinkedList<int>"* %11, align 4
  store %"bsl::lib::Lists::LinkedList<int>"* %11, %"bsl::lib::Lists::LinkedList<int>"** %ptr, align 8
  store i1 true, i1* %shouldLoop, align 1
  %shouldLoop2 = load i1, i1* %shouldLoop, align 1
  br i1 %shouldLoop2, label %loop, label %rest13

loop:                                             ; preds = %match-cont, %entry
  %ptr3 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ptr, align 8
  %12 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ptr3, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %12, %"bsl::lib::Lists::LinkedList<int>"* %lst, align 4
  %len4 = load i32, i32* %len, align 4
  %13 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  %14 = load i32, i32* %13, align 4
  %15 = icmp sle i32 %14, %len4
  br i1 %15, label %then, label %else9

then:                                             ; preds = %loop
  %16 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  %17 = load i32, i32* %16, align 4
  %18 = icmp sle i32 %17, %len4
  br i1 %18, label %then5, label %else8

then5:                                            ; preds = %then
  %19 = mul nsw i32 %len4, 2
  %20 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  %21 = load i32, i32* %20, align 4
  %22 = icmp sge i32 %19, %21
  br i1 %22, label %then6, label %else

then6:                                            ; preds = %then5
  %23 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 0
  %24 = load volatile i32*, i32** %23, align 8
  %25 = sext i32 %19 to i64
  %26 = mul nsw i64 %25, 4
  %27 = call i8* @GC_malloc(i64 %26)
  %28 = bitcast i8* %27 to i32*
  store i32 0, i32* %2, align 4
  %29 = load i32, i32* %2, align 4
  %30 = icmp slt i32 %29, %21
  br i1 %30, label %loop7, label %rest

loop7:                                            ; preds = %loop7, %then6
  %31 = load i32, i32* %2, align 4
  %32 = getelementptr i32, i32* %24, i32 %31
  %33 = load i32, i32* %32, align 4
  %34 = getelementptr i32, i32* %28, i32 %31
  store i32 %33, i32* %34, align 4
  %35 = add nsw i32 %31, 1
  store i32 %35, i32* %2, align 4
  %36 = load i32, i32* %2, align 4
  %37 = icmp slt i32 %36, %21
  br i1 %37, label %loop7, label %rest

rest:                                             ; preds = %loop7, %then6
  store i32* %28, i32** %23, align 8
  %38 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 2
  store i32 %19, i32* %38, align 4
  br label %else

else:                                             ; preds = %rest, %then5
  br label %else8

else8:                                            ; preds = %else, %then
  %39 = add nsw i32 %len4, 1
  store i32 %39, i32* %13, align 4
  br label %else9

else9:                                            ; preds = %else8, %loop
  %40 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 0
  %41 = load volatile i32*, i32** %40, align 8
  %42 = getelementptr i32, i32* %41, i32 %len4
  %43 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %lst, i32 0, i32 1
  %44 = load i32, i32* %43, align 4
  store i32 %44, i32* %42, align 4
  %45 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %lst, i32 0, i32 0
  %46 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %45, align 4
  store %"(Box<LinkedList<int>> + Empty)" %46, %"(Box<LinkedList<int>> + Empty)"* %1, align 4
  %47 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 0
  %48 = load i32, i32* %47, align 4
  switch i32 %48, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %else9
  %49 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 1
  %50 = bitcast [8 x i8]* %49 to %"bsl::lib::Lists::LinkedList<int>"**
  %51 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %50, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %51, %"bsl::lib::Lists::LinkedList<int>"** %nxt, align 8
  %nxt10 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %nxt, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %nxt10, %"bsl::lib::Lists::LinkedList<int>"** %ptr, align 8
  %len11 = load i32, i32* %len, align 4
  %52 = add nsw i32 %len11, 1
  store i32 %52, i32* %len, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %else9
  %53 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 1
  %54 = bitcast [8 x i8]* %53 to %"bsl::lib::Types::Empty"*
  %55 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %54, align 1
  store %"bsl::lib::Types::Empty" %55, %"bsl::lib::Types::Empty"* %e, align 1
  store i1 false, i1* %shouldLoop, align 1
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %else9
  %shouldLoop12 = load i1, i1* %shouldLoop, align 1
  br i1 %shouldLoop12, label %loop, label %rest13

rest13:                                           ; preds = %match-cont, %entry
  %ans14 = load %"int[]", %"int[]"* %ans, align 8
  ret %"int[]" %ans14
}

declare i8* @GC_malloc(i64)

define private %Unit @"program::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %1 = call %Unit (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32 %i1)
  ret %Unit zeroinitializer
}

declare %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]", %Unit (i32)*)

declare i8* @malloc(i32)

declare %Unit @_WriteChannel(%_Channel*, i8*)
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


    VirtualInput * bsl_lib_types = getVI("../../bsl/lib/Types.bismuth", {"bsl", "lib", "Types"});
    VirtualInput * bsl_lib_lists = getVI("../../bsl/lib/Lists.bismuth", {"bsl", "lib", "Lists"});
    VirtualInput * bsl_lib_optional = getVI("../../bsl/lib/Optional.bismuth", {"bsl", "lib", "Optional"});
    VirtualInput * bsl_lib_arrays = getVI("../../bsl/lib/Arrays.bismuth", {"bsl", "lib", "Arrays"});

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
  %ele.0 = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %2 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %3 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %4 = alloca %"bsl::lib::Types::Empty", align 8
  %i.0 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %nxt.0 = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %5 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %shouldLoop.0 = alloca i1, align 1
  %idx = alloca i32, align 4
  %origPtr.0 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %ansConstPtr = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %ansPtr.0 = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %6 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %7 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %8 = alloca %"bsl::lib::Types::Empty", align 8
  %m2 = alloca i32 (i32, i32)*, align 8
  %e = alloca %"bsl::lib::Types::Empty", align 8
  %a = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %ele = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %9 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %10 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %11 = alloca %"bsl::lib::Types::Empty", align 8
  %i = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %nxt = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %12 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %shouldLoop = alloca i1, align 1
  %origPtr = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %ansPtr = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %ans = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %13 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %14 = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %15 = alloca %"bsl::lib::Types::Empty", align 8
  %m1 = alloca i32 (i32)*, align 8
  %16 = alloca %"(int -> int + int, int -> int)", align 8
  %mapper = alloca %"(int -> int + int, int -> int)", align 8
  %array = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  store %"bsl::lib::Lists::LinkedList<int>" %0, %"bsl::lib::Lists::LinkedList<int>"* %array, align 4
  store %"(int -> int + int, int -> int)" %1, %"(int -> int + int, int -> int)"* %mapper, align 4
  %mapper1 = load %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %mapper, align 4
  store %"(int -> int + int, int -> int)" %mapper1, %"(int -> int + int, int -> int)"* %16, align 4
  %17 = getelementptr %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %16, i32 0, i32 0
  %18 = load i32, i32* %17, align 4
  switch i32 %18, label %match-cont33 [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch214
  ]

tagBranch1:                                       ; preds = %entry
  %19 = getelementptr %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %16, i32 0, i32 1
  %20 = bitcast [8 x i8]* %19 to i32 (i32)**
  %21 = load i32 (i32)*, i32 (i32)** %20, align 8
  store i32 (i32)* %21, i32 (i32)** %m1, align 8
  %22 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %15, align 1
  %23 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %array, i32 0, i32 1
  %24 = load i32, i32* %23, align 4
  %m12 = load i32 (i32)*, i32 (i32)** %m1, align 8
  %25 = call i32 %m12(i32 %24)
  %26 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %13, i32 0, i32 0
  store i32 2, i32* %26, align 4
  %27 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %13, i32 0, i32 1
  %28 = bitcast [8 x i8]* %27 to %"bsl::lib::Types::Empty"*
  store %"bsl::lib::Types::Empty" %22, %"bsl::lib::Types::Empty"* %28, align 1
  %29 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %13, align 4
  %30 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %14, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %29, %"(Box<LinkedList<int>> + Empty)"* %30, align 4
  %31 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %14, i32 0, i32 1
  store i32 %25, i32* %31, align 4
  %32 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %14, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %32, %"bsl::lib::Lists::LinkedList<int>"* %ans, align 4
  %ans3 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ans, align 4
  %33 = call i8* @GC_malloc(i64 16)
  %34 = bitcast i8* %33 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %ans3, %"bsl::lib::Lists::LinkedList<int>"* %34, align 4
  store %"bsl::lib::Lists::LinkedList<int>"* %34, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr, align 8
  %35 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %array, i32 0, i32 0
  %36 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %35, align 4
  store %"(Box<LinkedList<int>> + Empty)" %36, %"(Box<LinkedList<int>> + Empty)"* %origPtr, align 4
  store i1 true, i1* %shouldLoop, align 1
  %shouldLoop4 = load i1, i1* %shouldLoop, align 1
  br i1 %shouldLoop4, label %loop, label %rest

loop:                                             ; preds = %match-cont, %tagBranch1
  %origPtr5 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %origPtr, align 4
  store %"(Box<LinkedList<int>> + Empty)" %origPtr5, %"(Box<LinkedList<int>> + Empty)"* %12, align 4
  %37 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %12, i32 0, i32 0
  %38 = load i32, i32* %37, align 4
  switch i32 %38, label %match-cont [
    i32 1, label %tagBranch16
    i32 2, label %tagBranch2
  ]

tagBranch16:                                      ; preds = %loop
  %39 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %12, i32 0, i32 1
  %40 = bitcast [8 x i8]* %39 to %"bsl::lib::Lists::LinkedList<int>"**
  %41 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %40, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %41, %"bsl::lib::Lists::LinkedList<int>"** %nxt, align 8
  %nxt7 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %nxt, align 8
  %42 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %nxt7, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %42, %"bsl::lib::Lists::LinkedList<int>"* %i, align 4
  %43 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %11, align 1
  %44 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %i, i32 0, i32 1
  %45 = load i32, i32* %44, align 4
  %m18 = load i32 (i32)*, i32 (i32)** %m1, align 8
  %46 = call i32 %m18(i32 %45)
  %47 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %9, i32 0, i32 0
  store i32 2, i32* %47, align 4
  %48 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %9, i32 0, i32 1
  %49 = bitcast [8 x i8]* %48 to %"bsl::lib::Types::Empty"*
  store %"bsl::lib::Types::Empty" %43, %"bsl::lib::Types::Empty"* %49, align 1
  %50 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %9, align 4
  %51 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %10, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %50, %"(Box<LinkedList<int>> + Empty)"* %51, align 4
  %52 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %10, i32 0, i32 1
  store i32 %46, i32* %52, align 4
  %53 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %10, align 4
  %54 = call i8* @GC_malloc(i64 16)
  %55 = bitcast i8* %54 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %53, %"bsl::lib::Lists::LinkedList<int>"* %55, align 4
  store %"bsl::lib::Lists::LinkedList<int>"* %55, %"bsl::lib::Lists::LinkedList<int>"** %ele, align 8
  %ansPtr9 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr, align 8
  %56 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ansPtr9, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %56, %"bsl::lib::Lists::LinkedList<int>"* %a, align 4
  %57 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %a, i32 0, i32 0
  %ele10 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ele, align 8
  %58 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %57, i32 0, i32 0
  store i32 1, i32* %58, align 4
  %59 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %57, i32 0, i32 1
  %60 = bitcast [8 x i8]* %59 to %"bsl::lib::Lists::LinkedList<int>"**
  store %"bsl::lib::Lists::LinkedList<int>"* %ele10, %"bsl::lib::Lists::LinkedList<int>"** %60, align 8
  %ele11 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ele, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %ele11, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr, align 8
  %61 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %i, i32 0, i32 0
  %62 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %61, align 4
  store %"(Box<LinkedList<int>> + Empty)" %62, %"(Box<LinkedList<int>> + Empty)"* %origPtr, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %loop
  %63 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %12, i32 0, i32 1
  %64 = bitcast [8 x i8]* %63 to %"bsl::lib::Types::Empty"*
  %65 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %64, align 1
  store %"bsl::lib::Types::Empty" %65, %"bsl::lib::Types::Empty"* %e, align 1
  store i1 false, i1* %shouldLoop, align 1
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch16, %loop
  %shouldLoop12 = load i1, i1* %shouldLoop, align 1
  br i1 %shouldLoop12, label %loop, label %rest

rest:                                             ; preds = %match-cont, %tagBranch1
  %ans13 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ans, align 4
  ret %"bsl::lib::Lists::LinkedList<int>" %ans13

tagBranch214:                                     ; preds = %entry
  %66 = getelementptr %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %16, i32 0, i32 1
  %67 = bitcast [8 x i8]* %66 to i32 (i32, i32)**
  %68 = load i32 (i32, i32)*, i32 (i32, i32)** %67, align 8
  store i32 (i32, i32)* %68, i32 (i32, i32)** %m2, align 8
  %69 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %8, align 1
  %70 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %array, i32 0, i32 1
  %71 = load i32, i32* %70, align 4
  %m215 = load i32 (i32, i32)*, i32 (i32, i32)** %m2, align 8
  %72 = call i32 %m215(i32 %71, i32 0)
  %73 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %6, i32 0, i32 0
  store i32 2, i32* %73, align 4
  %74 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %6, i32 0, i32 1
  %75 = bitcast [8 x i8]* %74 to %"bsl::lib::Types::Empty"*
  store %"bsl::lib::Types::Empty" %69, %"bsl::lib::Types::Empty"* %75, align 1
  %76 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %6, align 4
  %77 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %7, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %76, %"(Box<LinkedList<int>> + Empty)"* %77, align 4
  %78 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %7, i32 0, i32 1
  store i32 %72, i32* %78, align 4
  %79 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %7, align 4
  %80 = call i8* @GC_malloc(i64 16)
  %81 = bitcast i8* %80 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %79, %"bsl::lib::Lists::LinkedList<int>"* %81, align 4
  store %"bsl::lib::Lists::LinkedList<int>"* %81, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr.0, align 8
  %ansPtr.016 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr.0, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %ansPtr.016, %"bsl::lib::Lists::LinkedList<int>"** %ansConstPtr, align 8
  %82 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %array, i32 0, i32 0
  %83 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %82, align 4
  store %"(Box<LinkedList<int>> + Empty)" %83, %"(Box<LinkedList<int>> + Empty)"* %origPtr.0, align 4
  store i32 1, i32* %idx, align 4
  store i1 true, i1* %shouldLoop.0, align 1
  %shouldLoop.017 = load i1, i1* %shouldLoop.0, align 1
  br i1 %shouldLoop.017, label %loop18, label %rest31

loop18:                                           ; preds = %match-cont29, %tagBranch214
  %origPtr.019 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %origPtr.0, align 4
  store %"(Box<LinkedList<int>> + Empty)" %origPtr.019, %"(Box<LinkedList<int>> + Empty)"* %5, align 4
  %84 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %5, i32 0, i32 0
  %85 = load i32, i32* %84, align 4
  switch i32 %85, label %match-cont29 [
    i32 1, label %tagBranch120
    i32 2, label %tagBranch228
  ]

tagBranch120:                                     ; preds = %loop18
  %86 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %5, i32 0, i32 1
  %87 = bitcast [8 x i8]* %86 to %"bsl::lib::Lists::LinkedList<int>"**
  %88 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %87, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %88, %"bsl::lib::Lists::LinkedList<int>"** %nxt.0, align 8
  %nxt.021 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %nxt.0, align 8
  %89 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %nxt.021, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %89, %"bsl::lib::Lists::LinkedList<int>"* %i.0, align 4
  %90 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %4, align 1
  %91 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %i.0, i32 0, i32 1
  %92 = load i32, i32* %91, align 4
  %idx22 = load i32, i32* %idx, align 4
  %m223 = load i32 (i32, i32)*, i32 (i32, i32)** %m2, align 8
  %93 = call i32 %m223(i32 %92, i32 %idx22)
  %94 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %2, i32 0, i32 0
  store i32 2, i32* %94, align 4
  %95 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %2, i32 0, i32 1
  %96 = bitcast [8 x i8]* %95 to %"bsl::lib::Types::Empty"*
  store %"bsl::lib::Types::Empty" %90, %"bsl::lib::Types::Empty"* %96, align 1
  %97 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %2, align 4
  %98 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %3, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %97, %"(Box<LinkedList<int>> + Empty)"* %98, align 4
  %99 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %3, i32 0, i32 1
  store i32 %93, i32* %99, align 4
  %100 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %3, align 4
  %101 = call i8* @GC_malloc(i64 16)
  %102 = bitcast i8* %101 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %100, %"bsl::lib::Lists::LinkedList<int>"* %102, align 4
  store %"bsl::lib::Lists::LinkedList<int>"* %102, %"bsl::lib::Lists::LinkedList<int>"** %ele.0, align 8
  %idx24 = load i32, i32* %idx, align 4
  %103 = add nsw i32 %idx24, 1
  store i32 %103, i32* %idx, align 4
  %ansPtr.025 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr.0, align 8
  %104 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ansPtr.025, i32 0, i32 0
  %ele.026 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ele.0, align 8
  %105 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %104, i32 0, i32 0
  store i32 1, i32* %105, align 4
  %106 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %104, i32 0, i32 1
  %107 = bitcast [8 x i8]* %106 to %"bsl::lib::Lists::LinkedList<int>"**
  store %"bsl::lib::Lists::LinkedList<int>"* %ele.026, %"bsl::lib::Lists::LinkedList<int>"** %107, align 8
  %ele.027 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ele.0, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %ele.027, %"bsl::lib::Lists::LinkedList<int>"** %ansPtr.0, align 8
  %108 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %i.0, i32 0, i32 0
  %109 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %108, align 4
  store %"(Box<LinkedList<int>> + Empty)" %109, %"(Box<LinkedList<int>> + Empty)"* %origPtr.0, align 4
  br label %match-cont29

tagBranch228:                                     ; preds = %loop18
  %110 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %5, i32 0, i32 1
  %111 = bitcast [8 x i8]* %110 to %"bsl::lib::Types::Empty"*
  %112 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %111, align 1
  store %"bsl::lib::Types::Empty" %112, %"bsl::lib::Types::Empty"* %e.0, align 1
  store i1 false, i1* %shouldLoop.0, align 1
  br label %match-cont29

match-cont29:                                     ; preds = %tagBranch228, %tagBranch120, %loop18
  %shouldLoop.030 = load i1, i1* %shouldLoop.0, align 1
  br i1 %shouldLoop.030, label %loop18, label %rest31

rest31:                                           ; preds = %match-cont29, %tagBranch214
  %ansConstPtr32 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ansConstPtr, align 8
  %113 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ansConstPtr32, align 4
  ret %"bsl::lib::Lists::LinkedList<int>" %113

match-cont33:                                     ; preds = %entry
  unreachable
}

declare i8* @GC_malloc(i64)
)""");

    REQUIRE(bsl_lib_optional->getIrStr() ==
R"(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"
)");

    REQUIRE(bsl_lib_arrays->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%"int[]" = type { i32*, i32, i32 }
%"(Unit + int)" = type { i32, [4 x i8] }

define %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %0, %Unit (i32)* %1) {
entry:
  %t = alloca i32, align 4
  %u = alloca %Unit, align 8
  %2 = alloca %"(Unit + int)", align 8
  %3 = alloca %"(Unit + int)", align 8
  %4 = alloca %"(Unit + int)", align 8
  %i = alloca i32, align 4
  %fn = alloca %Unit (i32)*, align 8
  %array = alloca %"int[]", align 8
  store %"int[]" %0, %"int[]"* %array, align 8
  store %Unit (i32)* %1, %Unit (i32)** %fn, align 8
  store i32 0, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %5 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 1
  %6 = load i32, i32* %5, align 4
  %7 = icmp slt i32 %i1, %6
  br i1 %7, label %loop, label %rest

loop:                                             ; preds = %match-cont, %entry
  %i2 = load i32, i32* %i, align 4
  %8 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 1
  %9 = load i32, i32* %8, align 4
  %10 = icmp slt i32 %i2, %9
  br i1 %10, label %accessLTL, label %accessBad

accessLTL:                                        ; preds = %loop
  %11 = icmp sge i32 %i2, 0
  br i1 %11, label %accessGTZ, label %accessBad

accessGTZ:                                        ; preds = %accessLTL
  %12 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 0
  %13 = load i32*, i32** %12, align 8
  %14 = getelementptr i32, i32* %13, i32 %i2
  %15 = load i32, i32* %14, align 4
  %16 = getelementptr %"(Unit + int)", %"(Unit + int)"* %4, i32 0, i32 0
  store i32 2, i32* %16, align 4
  %17 = getelementptr %"(Unit + int)", %"(Unit + int)"* %4, i32 0, i32 1
  %18 = bitcast [4 x i8]* %17 to i32*
  store i32 %15, i32* %18, align 4
  %19 = load %"(Unit + int)", %"(Unit + int)"* %4, align 4
  br label %accessAfter

accessBad:                                        ; preds = %accessLTL, %loop
  %20 = getelementptr %"(Unit + int)", %"(Unit + int)"* %3, i32 0, i32 0
  store i32 1, i32* %20, align 4
  %21 = getelementptr %"(Unit + int)", %"(Unit + int)"* %3, i32 0, i32 1
  %22 = bitcast [4 x i8]* %21 to %Unit*
  store %Unit zeroinitializer, %Unit* %22, align 1
  %23 = load %"(Unit + int)", %"(Unit + int)"* %3, align 4
  br label %accessAfter

accessAfter:                                      ; preds = %accessBad, %accessGTZ
  %arrayAccess = phi %"(Unit + int)" [ %19, %accessGTZ ], [ %23, %accessBad ]
  store %"(Unit + int)" %arrayAccess, %"(Unit + int)"* %2, align 4
  %24 = getelementptr %"(Unit + int)", %"(Unit + int)"* %2, i32 0, i32 0
  %25 = load i32, i32* %24, align 4
  switch i32 %25, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %accessAfter
  %26 = getelementptr %"(Unit + int)", %"(Unit + int)"* %2, i32 0, i32 1
  %27 = bitcast [4 x i8]* %26 to %Unit*
  %28 = load %Unit, %Unit* %27, align 1
  store %Unit %28, %Unit* %u, align 1
  br label %match-cont

tagBranch2:                                       ; preds = %accessAfter
  %29 = getelementptr %"(Unit + int)", %"(Unit + int)"* %2, i32 0, i32 1
  %30 = bitcast [4 x i8]* %29 to i32*
  %31 = load i32, i32* %30, align 4
  store i32 %31, i32* %t, align 4
  %t3 = load i32, i32* %t, align 4
  %fn4 = load %Unit (i32)*, %Unit (i32)** %fn, align 8
  %32 = call %Unit %fn4(i32 %t3)
  br label %match-cont

match-cont:                                       ; preds = %tagBranch2, %tagBranch1, %accessAfter
  %i5 = load i32, i32* %i, align 4
  %33 = add nsw i32 %i5, 1
  store i32 %33, i32* %i, align 4
  %i6 = load i32, i32* %i, align 4
  %34 = getelementptr %"int[]", %"int[]"* %array, i32 0, i32 1
  %35 = load i32, i32* %34, align 4
  %36 = icmp slt i32 %i6, %35
  br i1 %36, label %loop, label %rest

rest:                                             ; preds = %match-cont, %entry
  ret %Unit zeroinitializer
}
)""");

    REQUIRE(temp->getIrStr() == 
R"""(; ModuleID = 'BismuthProgram'
source_filename = "BismuthProgram"

%Unit = type {}
%_Channel = type opaque
%"bsl::lib::Lists::LinkedList<int>" = type { %"(Box<LinkedList<int>> + Empty)", i32 }
%"(Box<LinkedList<int>> + Empty)" = type { i32, [8 x i8] }
%"(int -> int + int, int -> int)" = type { i32, [8 x i8] }
%"int[]" = type { i32*, i32, i32 }
%"bsl::lib::Types::Empty" = type {}

@0 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@1 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@2 = private unnamed_addr constant [5 x i8] c"%u, \00", align 1
@3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1

define %Unit @program(%_Channel* %0) {
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
  %c = alloca %_Channel*, align 8
  store %_Channel* %0, %_Channel** %c, align 8
  %7 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %6, align 1
  %8 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %4, i32 0, i32 0
  store i32 2, i32* %8, align 4
  %9 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %4, i32 0, i32 1
  %10 = bitcast [8 x i8]* %9 to %"bsl::lib::Types::Empty"*
  store %"bsl::lib::Types::Empty" %7, %"bsl::lib::Types::Empty"* %10, align 1
  %11 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %4, align 4
  %12 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %5, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %11, %"(Box<LinkedList<int>> + Empty)"* %12, align 4
  %13 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %5, i32 0, i32 1
  store i32 2, i32* %13, align 4
  %14 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %5, align 4
  %15 = call i8* @GC_malloc(i64 16)
  %16 = bitcast i8* %15 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %14, %"bsl::lib::Lists::LinkedList<int>"* %16, align 4
  %17 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %2, i32 0, i32 0
  store i32 1, i32* %17, align 4
  %18 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %2, i32 0, i32 1
  %19 = bitcast [8 x i8]* %18 to %"bsl::lib::Lists::LinkedList<int>"**
  store %"bsl::lib::Lists::LinkedList<int>"* %16, %"bsl::lib::Lists::LinkedList<int>"** %19, align 8
  %20 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %2, align 4
  %21 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %3, i32 0, i32 0
  store %"(Box<LinkedList<int>> + Empty)" %20, %"(Box<LinkedList<int>> + Empty)"* %21, align 4
  %22 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %3, i32 0, i32 1
  store i32 1, i32* %22, align 4
  %23 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %3, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %23, %"bsl::lib::Lists::LinkedList<int>"* %a, align 4
  %a1 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %a, align 4
  %24 = call %"int[]" @"temp3::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %a1)
  store %"int[]" %24, %"int[]"* %b, align 8
  %b2 = load %"int[]", %"int[]"* %b, align 8
  %25 = call %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %b2, %Unit (i32)* @"program::#lambda")
  %26 = call %Unit (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @1, i32 0, i32 0))
  %a3 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %a, align 4
  %27 = getelementptr %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %1, i32 0, i32 0
  store i32 2, i32* %27, align 4
  %28 = getelementptr %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %1, i32 0, i32 1
  %29 = bitcast [8 x i8]* %28 to i32 (i32, i32)**
  store i32 (i32, i32)* @"program::#lambda.0", i32 (i32, i32)** %29, align 8
  %30 = load %"(int -> int + int, int -> int)", %"(int -> int + int, int -> int)"* %1, align 4
  %31 = call %"bsl::lib::Lists::LinkedList<int>" @"bsl::lib::Lists::map<int, int>"(%"bsl::lib::Lists::LinkedList<int>" %a3, %"(int -> int + int, int -> int)" %30)
  store %"bsl::lib::Lists::LinkedList<int>" %31, %"bsl::lib::Lists::LinkedList<int>"* %mapped, align 4
  %mapped4 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %mapped, align 4
  %32 = call %"int[]" @"temp3::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %mapped4)
  %33 = call %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]" %32, %Unit (i32)* @"program::#lambda.1")
  %34 = call %Unit (i8*, ...) @printf(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @3, i32 0, i32 0))
  %35 = call i8* @malloc(i32 4)
  %36 = bitcast i8* %35 to i32*
  store i32 0, i32* %36, align 4
  %37 = load %_Channel*, %_Channel** %c, align 8
  %38 = call %Unit @_WriteChannel(%_Channel* %37, i8* %35)
  ret %Unit zeroinitializer
}

declare %Unit @printf(i8*, ...)

define %"int[]" @"temp3::linkedListToDyn<int>"(%"bsl::lib::Lists::LinkedList<int>" %0) {
entry:
  %e = alloca %"bsl::lib::Types::Empty", align 8
  %nxt = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %1 = alloca %"(Box<LinkedList<int>> + Empty)", align 8
  %2 = alloca i32, align 4
  %lst = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  %ptr = alloca %"bsl::lib::Lists::LinkedList<int>"*, align 8
  %len = alloca i32, align 4
  %ans = alloca %"int[]", align 8
  %list = alloca %"bsl::lib::Lists::LinkedList<int>", align 8
  store %"bsl::lib::Lists::LinkedList<int>" %0, %"bsl::lib::Lists::LinkedList<int>"* %list, align 4
  %3 = sext i32 2 to i64
  %4 = mul nsw i64 %3, 4
  %5 = call i8* @GC_malloc(i64 %4)
  %6 = bitcast i8* %5 to i32*
  %7 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 0
  store i32* %6, i32** %7, align 8
  %8 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  store i32 1, i32* %8, align 4
  %9 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 2
  store i32 2, i32* %9, align 4
  store i32 0, i32* %len, align 4
  %list1 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %list, align 4
  %10 = call i8* @GC_malloc(i64 16)
  %11 = bitcast i8* %10 to %"bsl::lib::Lists::LinkedList<int>"*
  store %"bsl::lib::Lists::LinkedList<int>" %list1, %"bsl::lib::Lists::LinkedList<int>"* %11, align 4
  store %"bsl::lib::Lists::LinkedList<int>"* %11, %"bsl::lib::Lists::LinkedList<int>"** %ptr, align 8
  br i1 true, label %loop, label %rest12

loop:                                             ; preds = %match-cont, %entry
  %ptr2 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %ptr, align 8
  %12 = load %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %ptr2, align 4
  store %"bsl::lib::Lists::LinkedList<int>" %12, %"bsl::lib::Lists::LinkedList<int>"* %lst, align 4
  %len3 = load i32, i32* %len, align 4
  %13 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  %14 = load i32, i32* %13, align 4
  %15 = icmp sle i32 %14, %len3
  br i1 %15, label %then, label %else8

then:                                             ; preds = %loop
  %16 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  %17 = load i32, i32* %16, align 4
  %18 = icmp sle i32 %17, %len3
  br i1 %18, label %then4, label %else7

then4:                                            ; preds = %then
  %19 = mul nsw i32 %len3, 2
  %20 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 1
  %21 = load i32, i32* %20, align 4
  %22 = icmp sge i32 %19, %21
  br i1 %22, label %then5, label %else

then5:                                            ; preds = %then4
  %23 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 0
  %24 = load volatile i32*, i32** %23, align 8
  %25 = sext i32 %19 to i64
  %26 = mul nsw i64 %25, 4
  %27 = call i8* @GC_malloc(i64 %26)
  %28 = bitcast i8* %27 to i32*
  store i32 0, i32* %2, align 4
  %29 = load i32, i32* %2, align 4
  %30 = icmp slt i32 %29, %21
  br i1 %30, label %loop6, label %rest

loop6:                                            ; preds = %loop6, %then5
  %31 = load i32, i32* %2, align 4
  %32 = getelementptr i32, i32* %24, i32 %31
  %33 = load i32, i32* %32, align 4
  %34 = getelementptr i32, i32* %28, i32 %31
  store i32 %33, i32* %34, align 4
  %35 = add nsw i32 %31, 1
  store i32 %35, i32* %2, align 4
  %36 = load i32, i32* %2, align 4
  %37 = icmp slt i32 %36, %21
  br i1 %37, label %loop6, label %rest

rest:                                             ; preds = %loop6, %then5
  store i32* %28, i32** %23, align 8
  %38 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 2
  store i32 %19, i32* %38, align 4
  br label %else

else:                                             ; preds = %rest, %then4
  br label %else7

else7:                                            ; preds = %else, %then
  %39 = add nsw i32 %len3, 1
  store i32 %39, i32* %13, align 4
  br label %else8

else8:                                            ; preds = %else7, %loop
  %40 = getelementptr %"int[]", %"int[]"* %ans, i32 0, i32 0
  %41 = load volatile i32*, i32** %40, align 8
  %42 = getelementptr i32, i32* %41, i32 %len3
  %43 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %lst, i32 0, i32 1
  %44 = load i32, i32* %43, align 4
  store i32 %44, i32* %42, align 4
  %45 = getelementptr %"bsl::lib::Lists::LinkedList<int>", %"bsl::lib::Lists::LinkedList<int>"* %lst, i32 0, i32 0
  %46 = load %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %45, align 4
  store %"(Box<LinkedList<int>> + Empty)" %46, %"(Box<LinkedList<int>> + Empty)"* %1, align 4
  %47 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 0
  %48 = load i32, i32* %47, align 4
  switch i32 %48, label %match-cont [
    i32 1, label %tagBranch1
    i32 2, label %tagBranch2
  ]

tagBranch1:                                       ; preds = %else8
  %49 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 1
  %50 = bitcast [8 x i8]* %49 to %"bsl::lib::Lists::LinkedList<int>"**
  %51 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %50, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %51, %"bsl::lib::Lists::LinkedList<int>"** %nxt, align 8
  %nxt9 = load %"bsl::lib::Lists::LinkedList<int>"*, %"bsl::lib::Lists::LinkedList<int>"** %nxt, align 8
  store %"bsl::lib::Lists::LinkedList<int>"* %nxt9, %"bsl::lib::Lists::LinkedList<int>"** %ptr, align 8
  %len10 = load i32, i32* %len, align 4
  %52 = add nsw i32 %len10, 1
  store i32 %52, i32* %len, align 4
  br label %match-cont

tagBranch2:                                       ; preds = %else8
  %53 = getelementptr %"(Box<LinkedList<int>> + Empty)", %"(Box<LinkedList<int>> + Empty)"* %1, i32 0, i32 1
  %54 = bitcast [8 x i8]* %53 to %"bsl::lib::Types::Empty"*
  %55 = load %"bsl::lib::Types::Empty", %"bsl::lib::Types::Empty"* %54, align 1
  store %"bsl::lib::Types::Empty" %55, %"bsl::lib::Types::Empty"* %e, align 1
  %ans11 = load %"int[]", %"int[]"* %ans, align 8
  ret %"int[]" %ans11

match-cont:                                       ; preds = %tagBranch1, %else8
  br i1 true, label %loop, label %rest12

rest12:                                           ; preds = %match-cont, %entry
  %ans13 = load %"int[]", %"int[]"* %ans, align 8
  ret %"int[]" %ans13
}

declare i8* @GC_malloc(i64)

define private %Unit @"program::#lambda"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %1 = call %Unit (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @0, i32 0, i32 0), i32 %i1)
  ret %Unit zeroinitializer
}

declare %Unit @"bsl::lib::Arrays::forEach<int>"(%"int[]", %Unit (i32)*)

define private i32 @"program::#lambda.0"(i32 %0, i32 %1) {
entry:
  %idx = alloca i32, align 4
  %val = alloca i32, align 4
  store i32 %0, i32* %val, align 4
  store i32 %1, i32* %idx, align 4
  %val1 = load i32, i32* %val, align 4
  %2 = add nsw i32 %val1, 1
  %idx2 = load i32, i32* %idx, align 4
  %3 = add nsw i32 %idx2, 1
  %4 = mul nsw i32 %2, %3
  ret i32 %4
}

declare %"bsl::lib::Lists::LinkedList<int>" @"bsl::lib::Lists::map<int, int>"(%"bsl::lib::Lists::LinkedList<int>", %"(int -> int + int, int -> int)")

define private %Unit @"program::#lambda.1"(i32 %0) {
entry:
  %i = alloca i32, align 4
  store i32 %0, i32* %i, align 4
  %i1 = load i32, i32* %i, align 4
  %1 = call %Unit (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @2, i32 0, i32 0), i32 %i1)
  ret %Unit zeroinitializer
}

declare i8* @malloc(i32)

declare %Unit @_WriteChannel(%_Channel*, i8*)
)""");
}
