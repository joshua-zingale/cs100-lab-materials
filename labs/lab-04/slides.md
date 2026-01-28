---
title: Unit Testing
subtitle: With Applications in GTest
author: Joshua Zingale
---

# Big Picture


> Unit testing, a.k.a. component or module testing, is a form of software testing by which isolated source code is tested to validate expected behavior.^[[https://en.wikipedia.org/wiki/Unit_testing](https://en.wikipedia.org/wiki/Unit_testing)]


Unit tests

- catch bugs close to their source,
- diagnose problematic sections of code,
- can provide an empirical measure of progress,
- and are bettered by careful code-base design.

# Concept: Focused Tests

Each test should evaluate a unique feature/case thoroughly.

::: { .columns }

:::: { .column width="50%" }
## Okay

\tiny
```python
def test_add():
    assert add(3,4) == 7
    assert add(1, 8) == 9
    assert add(-3,-4) == -7
    assert add(-1, -8) == -9
    assert add(-3,4) == 1
    assert add(-1, 8) == 7
    assert add(4294967295,1) == 4294967296
    ...
```
\normalsize
::::
:::: { .column width="50%" }
## Better

\tiny
```python
def test_add_positive_numbers():
    assert add(3,4) == 7
    assert add(1, 8) == 9
def test_add_negative_numbers():
    assert add(-3,-4) == -7
    assert add(-1, -8) == -9
def test_add_mixed_numbers():
    assert add(-3,4) == 1
    assert add(-1, 8) == 7
def test_add_overflow_recovery():
    assert add(4294967295,1) == 4294967296
    ...
...
```
\normalsize
::::
:::


# Designing to Be Tested

Unit testing can only work if the code base is easily compartmentalizable.
To accomplish this,

- have a clear hierarchical, better shallow, dependency structure;
- utilize *dependency injection* wherever possible;
    - e.g. instead of hard coding a database into `WebServer`, have the webserver take the database as an argument, like `server = WebServer(database=db_object)`
- develop small components, e.g. functions, classes, objects, that have well-defined and minimally-scoped functionality.


# Concept: Stubbing { .shrink }

Problem: *Component A requires specific data from Component B to complete a logic path, but Component B is a slow database or an external API.*

Solution: *Create a **Stub** that provides "canned" responses.*

## Example
::: { .columns }

:::: { .column width="50%" }

\tiny
```python
    class StubTaxProvider:
        """A 'dumb' object type that provides 
        predefined data for the test."""
        def __init__(zip_to_rates: dict[int, float]):
            self._zip_to_rates = zip_to_rates
        def get_rate(self, zip_code):
            return self._zip_to_rates[zip_code]
```
\normalsize
::::
:::: { .column width="50%" }

\tiny
```python
def test_calculator_applies_tax_correctly():
    stub_taxes = StubTaxProvider({
        90210: 0.095
    })

    calc = TaxCalculator(
        tax_provider=stub_taxes)
    
    total = calc.calculate(
        amount=100.00, 
        zip_code="90210")
    
    assert total == 109.50
```
\normalsize
::::
:::


# Concept: Mock Objects { .shrink }

Problem: *I want a focused test for component A's use of B but component B's behavior cannot be tracked easily*

Solution: *Create a **Mock Objects** for component B and evaluate A's usage of B by injecting the mock objects as a dependency.*

## Example
::: { .columns }

:::: { .column width="50%" }

\tiny
```python
        class MockAuthService:
            def __init__(self, should_succeed):
                self.should_succeed = should_succeed
                self.call_count = 0
            def authenticate(self, credentials):
                self.call_count += 1
                return self.should_succeed
```
\normalsize
::::
:::: { .column width="50%" }

\tiny
```python
def test_login_uses_authentication_server():
    mock_auth = MockAuthService(
        should_succeed=True)
    creds = {
        "user": "joshua",
        "pass": "1234"}
    
    router = Router(
        auth_service=mock_auth)
    result = router.get(
        "/login",
        headers=encrypt(creds))
    
    assert mock_auth.call_count == 1
```
\normalsize
::::
:::


# Stubs vs. Mocks: The Key Difference

While the two are sometimes used interchangeably, it can be helpful to make a distinction.

| Feature | **Stub** | **Mock** |
| :--- | :--- | :--- |
| **Purpose** | To provide "canned" data to the system. | To verify interactions between objects. |
| **Focus** | **State:** Did we get the right output? | **Behavior:** Did we call the right method? |
| **Assertion** | Usually on the system's return value. | Usually on the Mock's call history. |



# Concept: Avoiding Brittle Tests

Problem: *Tests that fail on minor, non-functional changes (like fixing a typo in a log) are "brittle." They increase maintenance without adding value.*

Solution: *Test for **intent**, not exact strings. Use partial matches or property checks instead of checking every character.*

::: { .columns }


:::: { .column width="50%" }
## Overtested
\tiny
```python
def test_error_is_exact():
    # This fails if we change "User" 
    # to "Account" or add a period.
    result = login("joshua", "bad_pass")
    
    assert result.error == \
        "Error: User joshua not found!"
```
\normalsize
::::
:::: { .column width="50%" }
## Resilient

\tiny
```python
def test_error_contains_info():
    result = login("joshua", "bad_pass")
    
    # Check for the intent and data
    err = result.error.lower()
    assert "not found" in err
    assert "joshua" in err
```
\normalsize
::::
:::

# GTest: Basic Assertions { .shrink }

GTest provides a suite of macros to verify code behavior. **ASSERT** macros stop the test immediately, while **EXPECT** macros allow the test to continue after a failure.

## Example
\small
```cpp
TEST(CalculatorTest, HandlesBasicMath) {
    Calculator calc;
    
    // Standard equality check
    ASSERT_EQ(calc.add(2, 2), 4);
    
    // Testing for "Hard" failures (Crashes/Exits)
    // Ensures code exits when it's supposed to
    ASSERT_DEATH({
        calc.set_tax_rate(-1.0); 
    }, "Tax rate cannot be negative");
}
```
\normalsize


# GMock: Defining a Mock Object { .shrink }

In C++, we use the `MOCK_METHOD` macro. This creates a "shadow" implementation of an interface that GTest can track.

## Example
\small
```cpp
#include <gmock/gmock.h>

class AuthService {
public:
  virtual ~AuthService() {}
  virtual bool Authenticate(string user, string pass) = 0;
};

class MockAuthService : public AuthService {
public:
  MOCK_METHOD(bool, Authenticate,
    (string user, string pass),
    (override));
};
```
\normalsize

# GMock: Using the Mock in a Test

When using a Mock, you define the **Expectation** *before* you trigger the action.

## Example

\small
```cpp
TEST(RouterTest, ChecksAuthBeforeRouting) {

    MockAuthService mock_auth;
    Router router(&mock_auth);

    EXPECT_CALL(mock_auth, Authenticate(_, _))
        .Times(1)
        .WillOnce(Return(true));

    auto response = router.Get("/home");

    ASSERT_EQ(response.status, 200);
}
```
\normalsize