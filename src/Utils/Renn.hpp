#pragma once

#include <function2/function2.hpp>

namespace renn {

/*
 *
 *
 * While working on this, i got tired of saying "fiber/coroutine/task/job/whatever", so i "invented" my own term for "a scheduled executable unit" in this runtime.
 *
 * I call it a **renn** (from the German verb **_rennen_** - "to run").
 *
 * So, the scheduler doesn't really care what higher-level abstraction you use - it just runs renns
 * Maybe it is mildly confusing. But i don't care I just like building abstractions.
 *
 */

using Renn = fu2::unique_function<void()>;

};  // namespace renn
