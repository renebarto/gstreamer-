#pragma once

#include <thread>
#include <vector>
#include <core/CommandLineOption.h>
//#include <gstreamer++/element.h>
//#include <gstreamer++/elementfactory.h>
//#include <gstreamer++/errorlist.h>
//#include <gstreamer++/event.h>
//#include <gstreamer++/message.h>
//#include <gstreamer++/pipeline.h>
//#include <gstreamer++/query.h>
//#include <gstreamer++/registry.h>

struct _GMainLoop;

namespace GStreamer {

class Application
{
public:
    Application() = delete;
    Application(const Application & other) = delete;
    Application & operator = (const Application & other) = delete;
    Application(int argc, const char * argv[]);
    Application(int argc, const char * argv[], std::vector<Core::CommandLineOption::Ptr> applicationOptions);
    void Initialize();
//    bool InitializeChecked(ErrorList & errors);
    void Deinitialize();
    static bool IsInitialized() { return _initialized; }

    int MajorVersion() { return _majorVersion; }
    int MinorVersion() { return _minorVersion; }
    int MicroVersion() { return _microVersion; }
    int NanoVersion() { return _nanoVersion; }
    std::string VersionString();

    bool IsSegTrapEnabled();
    void SetSegTrapEnabled(bool enabled);

    bool IsRegistryForkEnabled();
    void SetRegistryForkEnabled(bool enabled);
    void UpdateRegistry();
//    RegistryPtr GetRegistry();

//    PipelinePtr CreatePipeline(const char * pipelineName);
//    BinPtr CreateBin(const char * binName);
//
//    ElementFactoryPtr GetElementFactory(const char * factoryName);
//    ElementPtr MakeElement(const char * factoryName, const char * elementName);
//
//    void Send(Element::Ptr target, const Event & event);
//    void Query(Element::Ptr target, const Query & query);
//    MessagePtr GetMessage() { return _pipeline->GetMessage(); }

    void Start();
    void Stop();
    void TriggerToStop();

//    virtual bool OnMessage(MessagePtr message);

private:
    void SetupCommandLineOptions();
    bool ParseApplicationParameters();
    void Thread();

    static bool _initialized;

    int _argc;
    const char * * _argv;
//    Pipeline::Ptr _pipeline;
    int _majorVersion;
    int _minorVersion;
    int _microVersion;
    int _nanoVersion;
    std::string applicationName;
    std::vector<Core::CommandLineOption::Ptr> _optionsGStreamer;
    std::vector<Core::CommandLineOption::Ptr> _optionsApplication;
    bool _parseApplicationOptions;
    std::thread _thread;
    _GMainLoop * _loop;
//    BusWatchID _busWatchID;
};

} // namespace GStreamer