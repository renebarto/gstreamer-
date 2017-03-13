#include <gstreamer++/application.h>

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;
using namespace GStreamer;

static const int VersionMajor = VERSION_MAJOR;
static const int VersionMinor = VERSION_MINOR;
static const int VersionMicro = VERSION_MICRO;
static const int VersionNano = VERSION_NANO;

bool Application::_initialized = false;

//static int BusCallback(GstBus * bus, GstMessage * message, void * data);

Application::Application(int argc, const char * argv[])
    : _argc(argc)
    , _argv(argv)
//    , _pipeline(nullptr)
    , _majorVersion(VersionMajor)
    , _minorVersion(VersionMinor)
    , _microVersion(VersionMicro)
    , _nanoVersion(VersionNano)
    , _optionsGStreamer()
    , _optionsApplication()
    , _parseApplicationOptions(false)
    , _thread()
    , _loop(nullptr)
//    , _busWatchID()
{
    SetupCommandLineOptions();
}

Application::Application(int argc, const char * argv[], std::vector<Core::CommandLineOption::Ptr> applicationOptions)
    : Application(argc, argv)
{
    _parseApplicationOptions = true;
    _optionsApplication = applicationOptions;
}

void Application::Initialize()
{
    assert(!_initialized);
    if (!_parseApplicationOptions)
    {

    }
    else
    {

    }
//    if ((_argc != 0) && !_parseApplicationOptions)
//        gst_init(&_argc, const_cast<char ***>(&_argv));
//    else
//        gst_init(nullptr, nullptr);
    if (_parseApplicationOptions)
    {
        assert(ParseApplicationParameters());
    }
    _initialized = true;
}

//bool Application::InitializeChecked(ErrorList & errors)
//{
//    errors.Clear();
//    if (_initialized)
//        errors.AddError(Error(ErrorCode::AlreadyInitialized));
//    GError * error;
//    bool result {};
//    if ((_argc != 0) && !_parseApplicationOptions)
//        result = gst_init_check(&_argc, const_cast<char ***>(&_argv), &error);
//    else
//        result = gst_init_check(nullptr, nullptr, &error);
//    if (_parseApplicationOptions && !ParseApplicationParameters())
//    {
//        Deinitialize();
//        return false;
//    }
//    _initialized = result;
//    return _initialized;
//}

void Application::Deinitialize()
{
    assert(_initialized);
//    gst_deinit();
    _initialized = false;
}

std::string Application::VersionString()
{
    std::ostringstream stream;
    stream << _majorVersion << "." << _minorVersion << "." << _microVersion << "." << _nanoVersion;
    return stream.str();
}

bool Application::IsSegTrapEnabled()
{
    assert(_initialized);
//    return gst_segtrap_is_enabled() != FALSE;
    return false;
}
void Application::SetSegTrapEnabled(bool enabled)
{
    assert(_initialized);
//    gst_segtrap_set_enabled(enabled ? TRUE : FALSE);
}

bool Application::IsRegistryForkEnabled()
{
    assert(_initialized);
//    return gst_registry_fork_is_enabled() != FALSE;
    return false;
}

void Application::SetRegistryForkEnabled(bool enabled)
{
    assert(_initialized);
//    gst_registry_fork_set_enabled(enabled ? TRUE : FALSE);
}

void Application::UpdateRegistry()
{
    assert(_initialized);
//    gst_update_registry();
}

bool Application::ParseApplicationParameters()
{
    applicationName = _argv[0];
//    GOptionEntry * optionEntries = new GOptionEntry[_optionsApplication.size() + 1];
//    for (size_t index = 0; index < _optionsApplication.size(); index++)
//    {
//        optionEntries[index].long_name = _optionsApplication[index].longName;
//        optionEntries[index].short_name = _optionsApplication[index].shortName;
//        optionEntries[index].flags = _optionsApplication[index].flags;
//        optionEntries[index].arg = static_cast<GOptionArg>(_optionsApplication[index].arg);
//        optionEntries[index].arg_data = _optionsApplication[index].argData;
//        optionEntries[index].description = _optionsApplication[index].description;
//        optionEntries[index].arg_description = _optionsApplication[index].argDescription;
//    }
//    optionEntries[_optionsApplication.size()] = { nullptr, '\0', 0, GOptionArg::G_OPTION_ARG_NONE, nullptr, nullptr, nullptr };
//
//    GOptionContext * context = g_option_context_new(applicationName.c_str());
//    g_option_context_add_main_entries(context, optionEntries, nullptr);
//    g_option_context_add_group(context, gst_init_get_option_group());
//
//    GError * err = nullptr;

    bool result = true;
//    if (!g_option_context_parse(context, &_argc, const_cast<char ***>(&_argv), &err))
//    {
//        std::cout << "Failed to initialize: " << err->message << std::endl;
//        g_clear_error(&err);
//        result = false;
//    }
//    g_option_context_free(context);
    return result;
}

//RegistryPtr Application::GetRegistry()
//{
//    return std::make_shared<Registry>(gst_registry_get());
//}
//
//PipelinePtr Application::CreatePipeline(const char * pipelineName)
//{
//    PipelinePtr pipeline = std::make_shared<Pipeline>(GST_PIPELINE(gst_pipeline_new(pipelineName)));
//    _busWatchID = pipeline->GetBus()->AddWatch(BusCallback, this);
//    return pipeline;
//}
//
//BinPtr Application::CreateBin(const char * binName)
//{
//    return std::make_shared<Bin>(GST_BIN(gst_bin_new(binName)));
//}
//
//ElementFactoryPtr Application::GetElementFactory(const char * factoryName)
//{
//    return std::make_shared<ElementFactory>(gst_element_factory_find(factoryName));
//}
//
//ElementPtr Application::MakeElement(const char * factoryName, const char * elementName)
//{
//    return std::make_shared<Element>(gst_element_factory_make(factoryName, elementName));
//}


void Application::Thread()
{
//    _loop = g_main_loop_new(nullptr, FALSE);
//    g_main_loop_run(_loop);
}

void Application::Start()
{
    _thread = std::thread(std::bind(&Application::Thread, this));
}

void Application::TriggerToStop()
{
//    if (_loop != nullptr)
//        g_main_loop_quit(_loop);
}

void Application::Stop()
{
    TriggerToStop();
    _thread.join();
//    g_source_remove(_busWatchID);
//    g_main_loop_unref(_loop);
//    _loop = nullptr;
//    _busWatchID = {};
}

//bool Application::OnMessage(MessagePtr message)
//{
//    cout << "Got " << message->GetTypeName() << " message" << endl;
//    switch (message->GetType())
//    {
//        case MessageType::Error:
//        {
//            cerr << "Error: " <<  message->GetContents() << " (" << message->GetDebugInfo() << ")" << endl;
//            TriggerToStop();
//            break;
//        }
//        case MessageType::EOS:
//            // end-of-stream
//            TriggerToStop();
//            break;
//        default:
//            // unhandled message
//            break;
//    }
//    // we want to be notified again the next time there is a message
//    // on the bus, so returning true (false means we want to stop watching
//    // for messages on the bus and our callback should not be called again)
//    return true;
//}

//static int BusCallback(GstBus * bus __attribute__((unused)), GstMessage * message, void * data)
//{
//    Application * pThis = reinterpret_cast<Application *>(data);
//
//    return pThis->OnMessage(std::make_shared<Message>(message)) ? TRUE : FALSE;
//}

void Application::SetupCommandLineOptions()
{

}
