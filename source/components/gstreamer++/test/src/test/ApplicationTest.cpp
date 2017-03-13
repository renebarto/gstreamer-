#include <unit-test-c++/UnitTestC++.h>

#include <memory>
#include <gstreamer++/application.h>

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
namespace GStreamer {
namespace Test {

class ApplicationTest : public UnitTestCpp::TestFixture
{
public:
    ApplicationTest()
        : argc(0)
        , argv(nullptr)
        , application(nullptr)
    {}

protected:
    virtual void SetUp() {}

    virtual void TearDown()
    {
        CleanupArgv();
        if (application->IsInitialized())
            application->Deinitialize();
    }

    void SetupArgv(const std::vector<std::string> & arguments)
    {
        CleanupArgv();
        argc = static_cast<int>(arguments.size());
        argv = new const char * [argc + 1];
        char * * tmp = const_cast<char * *>(argv);
        for (auto arg : arguments)
        {
            *tmp = new char[arg.length() + 1];
            strcpy(*tmp, arg.data());
            *(*tmp + arg.length()) = '\0';
            ++tmp;
        }
        *tmp = nullptr;
    }
    void CleanupArgv()
    {
        if (argv != nullptr)
        {
            const char * * tmp = argv;
            const char * arg = *tmp++;
            while (arg)
            {
                delete [] arg;
                arg = *tmp++;
            }
            delete [] argv;
            argv = nullptr;
            argc = 0;
        }
    }
    int argc;
    const char * * argv;
    shared_ptr<Application> application;
};

TEST_FIXTURE(ApplicationTest, Constructor)
{
    SetupArgv({ "App" });
    application = make_shared<Application>(argc, argv);

    EXPECT_FALSE(application->IsInitialized());
    EXPECT_EQ(0, application->MajorVersion());
    EXPECT_EQ(0, application->MinorVersion());
    EXPECT_EQ(1, application->MicroVersion());
    EXPECT_EQ(0, application->NanoVersion());
    EXPECT_NE("", application->VersionString());
}

TEST_FIXTURE(ApplicationTest, Initialize)
{
    SetupArgv({ "App" });
    application = make_shared<Application>(argc, argv);

    application->Initialize();

    EXPECT_TRUE(application->IsInitialized());
    EXPECT_NE("", application->VersionString());
}

//TEST_F(ApplicationTest, InitializeChecked)
//{
//    SetupArgv({ "App" });
//    Application app(argc, argv);
//    ErrorList errors;
//    EXPECT_TRUE(application->InitializeChecked(errors));
//
//    EXPECT_TRUE(application->IsInitialized()) << "Application should not be initialized";
//    EXPECT_NE(0, application->MajorVersion()) << "Version should be initialized";
//    EXPECT_NE("", application->VersionString()) << "Version should be initialized";
//}
//
//TEST_F(ApplicationTest, InitializeWithApplicationParameters)
//{
//    SetupArgv({ "App" });
//    bool verbose = false;
//    Application app(argc, argv, { OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""} });
//    ErrorList errors;
//    EXPECT_TRUE(application->InitializeChecked(errors));
//
//    EXPECT_TRUE(application->IsInitialized()) << "Application should not be initialized";
//    EXPECT_NE(0, application->MajorVersion()) << "Version should be initialized";
//    EXPECT_NE("", application->VersionString()) << "Version should be initialized";
//    EXPECT_FALSE(verbose);
//}
//
//TEST_F(ApplicationTest, InitializeWithApplicationParametersSpecifiedShort)
//{
//    SetupArgv({ "App", "-v" });
//    bool verbose = false;
//    Application app(argc, argv, { OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""} });
//    ErrorList errors;
//    EXPECT_TRUE(application->InitializeChecked(errors));
//
//    EXPECT_TRUE(application->IsInitialized()) << "Application should not be initialized";
//    EXPECT_NE(0, application->MajorVersion()) << "Version should be initialized";
//    EXPECT_NE("", application->VersionString()) << "Version should be initialized";
//    EXPECT_TRUE(verbose);
//}
//
//TEST_F(ApplicationTest, InitializeWithApplicationParametersSpecifiedLong)
//{
//    SetupArgv({ "App", "--verbose" });
//    bool verbose = false;
//    Application app(argc, argv, { OptionEntry{"verbose", 'v', 0, G_OPTION_ARG_NONE, &verbose, "Verbose output", ""} });
//    ErrorList errors;
//    EXPECT_TRUE(application->InitializeChecked(errors));
//
//    EXPECT_TRUE(application->IsInitialized()) << "Application should not be initialized";
//    EXPECT_NE(0, application->MajorVersion()) << "Version should be initialized";
//    EXPECT_NE("", application->VersionString()) << "Version should be initialized";
//    EXPECT_TRUE(verbose);
//}
//
//TEST_F(ApplicationTest, Deinitialize)
//{
//    SetupArgv({ "App" });
//    Application app(argc, argv);
//    application->Initialize();
//    application->Deinitialize();
//
//    EXPECT_FALSE(application->IsInitialized()) << "Application should not be initialized";
//    EXPECT_NE(0, application->MajorVersion()) << "Version should be initialized";
//    EXPECT_NE("", application->VersionString()) << "Version should be initialized";
//}

} // namespace Test
} // namespace GStreamer

#pragma clang diagnostic pop