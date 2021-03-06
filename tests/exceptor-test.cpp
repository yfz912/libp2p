#include <catch.hpp>

#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <p2p/utils/exceptor.h>

using namespace p2p;



enum ErrorCode {
    this_is_an_error = 1
};

namespace {
    const struct ErrorCode_category : std::error_category
    {
        const char* name() const noexcept override { return "ErrorCode"; }

        std::string message(int ev) const override
        {
            switch (static_cast<ErrorCode>(ev))
            {
            case ErrorCode::this_is_an_error:
                return "this is an error";

            default:
                return "(unrecognized error)";
            }
        }
    } errcat{};
}

std::error_code make_error_code(ErrorCode e)
{
return { static_cast<int>(e), errcat };
}

namespace std
{
    template <>
    struct is_error_code_enum<ErrorCode> : true_type {};
}



exceptor doSomethingRight() {
    return exceptor{};
}
exceptor doSomethingWrong() {
    return exceptor{ { ErrorCode::this_is_an_error } };
}

exceptor success()
{
    auto error = exceptor{};

    error = doSomethingRight();
    if (error) return error;

    error = doSomethingRight();
    if (error) return error;

    return error;
}

exceptor failure()
{
    auto error = exceptor{};

    error = doSomethingRight();
    if (error) return error;

    error = doSomethingWrong();
    if (error) return error;

    return error;
}


#define SHOULD_NOT_THROW_BECAUSE(reason, block) \
    { \
        bool catched = false; \
        try block catch (...) { catched = true; } \
        REQUIRE_FALSE(catched); \
    }
#define SHOULD_NOT_THROW(block) SHOULD_NOT_THROW_BECAUSE("", block)


#define SHOULD_THROW_BECAUSE(reason, block) \
    { \
        bool catched = false; \
        try block catch (...) { catched = true; } \
        REQUIRE(catched); \
    }
#define SHOULD_THROW(block) SHOULD_THROW_BECAUSE("", block)



TEST_CASE("Get return value and read it must not throw on error")
{
    SHOULD_NOT_THROW_BECAUSE("err is checked", {
        auto err = success();
        if (err) ; //handle error
    });

    SHOULD_NOT_THROW_BECAUSE("err is checked", {
        auto err = failure(); // uses exceptor(exceptor&&)
        if (err) ; //handle error
    });

    SHOULD_NOT_THROW_BECAUSE("err is checked", {
        auto err = exceptor{};
        
        err = failure(); // uses exceptor(exceptor&&)
        if (err) ; //handle error
    });
}

TEST_CASE("Get return value and don't read it must throw on error")
{
    SHOULD_NOT_THROW_BECAUSE("err is a success", {
        auto err = success();
    });

    SHOULD_THROW_BECAUSE("err is an failure and is not checked", {
        auto err = failure();
    });
}

TEST_CASE("Ignore return value must throw on error")
{
    SHOULD_NOT_THROW_BECAUSE("err is a success", {
        success();
    });

    SHOULD_THROW_BECAUSE("err is an failure and is not checked", {
        failure();
    });
}
TEST_CASE("Exceptor assignment")
{
    auto err = exceptor{};

    SHOULD_NOT_THROW_BECAUSE("err was defaulted", {
        err = success();
        if (err) ; //handle error
    });

    SHOULD_NOT_THROW_BECAUSE("err was checked before", {
        err = failure();
        if (err) ; //handle error
    });

    SHOULD_NOT_THROW_BECAUSE("err was checked before", {
        err = success();
    });

    SHOULD_NOT_THROW_BECAUSE("err was not checked before, but was a success", {
        err = failure();
    });

    SHOULD_THROW_BECAUSE("err was not checked before, and was a failure", {
        err = success();
    });

    if (err); //handle error
}
