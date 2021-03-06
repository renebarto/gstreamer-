#include <unit-test-c++/StreamTestReporter.h>

#include <cstdio>
#include <sstream>
#include <iomanip>
#include <unit-test-c++/TestDetails.h>
#include <unit-test-c++/TestDetailedResult.h>
#include <unit-test-c++/TestResults.h>

#include <osal/unused.h>

using namespace std;

namespace UnitTestCpp
{

const string StreamTestReporter::TestRunSeparator =     "[===========]";
const string StreamTestReporter::TestSuiteSeparator =   "[   SUITE   ]";
const string StreamTestReporter::TestFixtureSeparator = "[  FIXTURE  ]";
const string StreamTestReporter::TestSuccessSeparator = "[ SUCCEEDED ]";
const string StreamTestReporter::TestFailSeparator =    "[  FAILED   ]";

void StreamTestReporter::ReportTestRunStart(int numberOfTestSuites,
                                            int numberOfTestFixtures,
                                            int numberOfTests)
{
    _stream << TestRunSeparator << " "
           << TestRunStartMessage(numberOfTestSuites, numberOfTestFixtures, numberOfTests) << endl;
}

void StreamTestReporter::ReportTestRunFinish(int numberOfTestSuites,
                                             int numberOfTestFixtures,
                                             int numberOfTests,
                                             int milliSecondsElapsed)
{
    _stream << TestRunSeparator << " "
           << TestRunFinishMessage(numberOfTestSuites, numberOfTestFixtures, numberOfTests,
                                   milliSecondsElapsed) << endl;
}

void StreamTestReporter::ReportTestRunSummary(const TestResults * results, int milliSecondsElapsed)
{
    _stream << TestRunSummaryMessage(results, milliSecondsElapsed) << endl;
}

void StreamTestReporter::ReportTestRunOverview(const TestResults * results)
{
    _stream << TestRunOverviewMessage(results) << endl;
}

void StreamTestReporter::ReportTestSuiteStart(const string & suiteName,
                                              int numberOfTestFixtures)
{
    _stream << TestSuiteSeparator << " "
           << TestSuiteStartMessage(suiteName, numberOfTestFixtures) << endl;
}

void StreamTestReporter::ReportTestSuiteFinish(const string & suiteName,
                                               int numberOfTestFixtures,
                                               int milliSecondsElapsed)
{
    _stream << TestSuiteSeparator << " "
           << TestSuiteFinishMessage(suiteName, numberOfTestFixtures, milliSecondsElapsed) << endl;
}

void StreamTestReporter::ReportTestFixtureStart(const string & fixtureName,
                                                int numberOfTests)
{
    _stream << TestFixtureSeparator << " "
           << TestFixtureStartMessage(fixtureName, numberOfTests) << endl;
}

void StreamTestReporter::ReportTestFixtureFinish(const string & fixtureName,
                                                 int numberOfTests,
                                                 int milliSecondsElapsed)
{
    _stream << TestFixtureSeparator << " "
           << TestFixtureFinishMessage(fixtureName, numberOfTests, milliSecondsElapsed) << endl;
}

void StreamTestReporter::ReportTestStart(const TestDetails & details)
{
    DeferredTestReporter::ReportTestStart(details);
}

void StreamTestReporter::ReportTestFinish(const TestDetails & details, bool success,
                                          int milliSecondsElapsed)
{
    DeferredTestReporter::ReportTestFinish(details, success, milliSecondsElapsed);
    if (success)
        _stream << TestSuccessSeparator;
    else
        _stream << TestFailSeparator;

    _stream << " " << TestFinishMessage(details, success, milliSecondsElapsed) << endl;
}

void StreamTestReporter::ReportTestFailure(const TestDetails & details, const string & failure)
{
    DeferredTestReporter::ReportTestFailure(details, failure);
}

static string TestLiteral(int numberOfTests)
{
    return (numberOfTests == 1) ? "test" : "tests";
}

static string TestFailureLiteral(int numberOfTestFailures)
{
    return (numberOfTestFailures == 1) ? "failure" : "failures";
}

static string TestFixtureLiteral(int numberOfTestFixtures)
{
    return (numberOfTestFixtures == 1) ? "test fixture" : "test fixtures";
}

static string TestSuiteLiteral(int numberOfTestSuites)
{
    return (numberOfTestSuites == 1) ? "test suite" : "test suites";
}

static string TestSuiteName(string name)
{
    return (!name.empty()) ? name : "DefaultSuite";
}

static string TestFixtureName(string name)
{
    return (!name.empty()) ? name : "DefaultFixture";
}

string StreamTestReporter::TestRunStartMessage(int numberOfTestSuites,
                                               int numberOfTestFixtures,
                                               int numberOfTests)
{
    ostringstream stream;
    stream << "Running " << numberOfTests << " " << TestLiteral(numberOfTests)
           << " from " << numberOfTestFixtures << " " << TestFixtureLiteral(numberOfTestFixtures)
           << " in " << numberOfTestSuites << " " << TestSuiteLiteral(numberOfTestSuites) << " .";
    return stream.str();
}

string StreamTestReporter::TestRunFinishMessage(int numberOfTestSuites,
                                                int numberOfTestFixtures,
                                                int numberOfTests,
                                                int milliSecondsElapsed)
{
    ostringstream stream;
    stream << numberOfTests << " " << TestLiteral(numberOfTests)
           << " from " << numberOfTestFixtures << " " << TestFixtureLiteral(numberOfTestFixtures)
           << " in " << numberOfTestSuites << " " << TestSuiteLiteral(numberOfTestSuites)
           << " ran. (" << milliSecondsElapsed <<  " ms total)";
    return stream.str();
}

string StreamTestReporter::TestRunSummaryMessage(const TestResults * results,
                                                 int milliSecondsElapsed)
{
    ostringstream stream;

    if (results->GetFailureCount() > 0)
        stream << "FAILURE: " << results->GetFailedTestCount()
               << " out of " << results->GetTotalTestCount()
               << " tests failed (" << results->GetFailureCount() << " "
               << TestFailureLiteral(results->GetFailureCount()) << ")." << endl;
    else
        stream << "Success: " << results->GetTotalTestCount() << " "
               << TestLiteral(results->GetTotalTestCount()) << " passed." << endl;

    stream << "Test time: " << milliSecondsElapsed <<" ms." << endl;

    return stream.str();
}

string StreamTestReporter::TestRunOverviewMessage(const TestResults * results)
{
    ostringstream stream;

    if (results->GetFailureCount() > 0)
    {
        stream << "Failures:" << endl;
        for (auto testResult : Results())
        {
            if (testResult.Failed())
            {
                for (auto failure : testResult.Failures())
                    stream << testResult.fileName << ":" << failure.first << " : Failure in "
                           << TestName(testResult.suiteName, testResult.fixtureName,
                                       testResult.testName) << ": "
                           << failure.second << endl;
            }
        }
    }
    else
        stream << "No failures" << endl;

    return stream.str();
}

string StreamTestReporter::TestSuiteStartMessage(const string & suiteName,
                                                 int numberOfTestFixtures)
{
    ostringstream stream;
    stream << TestSuiteName(suiteName) << " (" << numberOfTestFixtures << " "
           << TestFixtureLiteral(numberOfTestFixtures) << ")";
    return stream.str();
}

string StreamTestReporter::TestSuiteFinishMessage(const string & suiteName,
                                                  int numberOfTestFixtures,
                                                  int milliSecondsElapsed)
{
    ostringstream stream;
    stream << numberOfTestFixtures << " " << TestFixtureLiteral(numberOfTestFixtures)
           << " from " << TestSuiteName(suiteName)
           << " (" << milliSecondsElapsed <<  " ms total)" << endl;
    return stream.str();
}

string StreamTestReporter::TestFixtureStartMessage(const string & fixtureName, int numberOfTests)
{
    ostringstream stream;
    stream << TestFixtureName(fixtureName)
           << " (" << numberOfTests << " " << TestLiteral(numberOfTests) << ")";
    return stream.str();
}

string StreamTestReporter::TestFixtureFinishMessage(const string & fixtureName, int numberOfTests,
                                                    int milliSecondsElapsed)
{
    ostringstream stream;
    stream << numberOfTests << " " << TestLiteral(numberOfTests)
           << " from " << TestFixtureName(fixtureName)
           << " (" << milliSecondsElapsed <<  " ms total)" << endl;
    return stream.str();
}

string StreamTestReporter::TestFinishMessage(const TestDetails & details,
                                             bool UNUSED(success),
                                             int milliSecondsElapsed)
{
    ostringstream stream;
    stream << TestName(details.suiteName, details.fixtureName, details.testName)
           << " (" << milliSecondsElapsed << " ms)";
    return stream.str();
}

string StreamTestReporter::TestName(const std::string & suiteName,
                                    const std::string & fixtureName,
                                    const std::string & testName)
{
    ostringstream stream;
    if (!suiteName.empty())
        stream << suiteName << "::";
    if (!fixtureName.empty())
        stream << fixtureName << "::";
    stream << testName;
    return stream.str();
}

} // namespace UnitTestCpp
