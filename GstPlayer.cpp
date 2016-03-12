#include "GstPlayer.h"


void GstPlayer::init(int &argc, char ***argv)
{
    gst_init (&argc, argv);
    _loop = g_main_loop_new (NULL, FALSE);
    _playElem = gst_element_factory_make ("playbin", "playElem");
    addBus();
    gst_element_set_state (_playElem, GST_STATE_READY); 
}

void GstPlayer::play(const std::string& uri)
{
    std::string gstUri = uri;
    if (!gst_uri_is_valid (gstUri.c_str())) 
    {
        gstUri = gst_filename_to_uri (gstUri.c_str(), NULL);
    }
    g_object_set (G_OBJECT (_playElem), "uri", uri.c_str(), NULL); 
    gst_element_set_state (_playElem, GST_STATE_PLAYING);
    runLoop();
}

void GstPlayer::pause()
{
    gst_element_set_state (_playElem, GST_STATE_PAUSED);
}

void GstPlayer::stop()
{
    gst_element_set_state (_playElem, GST_STATE_NULL);  
}

GstPlayer::~GstPlayer()
{
    stop();
    gst_object_unref (GST_OBJECT (_playElem));
}

void GstPlayer::runLoop()
{
    if(!_isLooping)
    {
        _mainLoop = std::thread(g_main_loop_run, _loop);
        _isLooping = true;
    }
}

void GstPlayer::quit()
{
    g_main_loop_quit(_loop);
    _mainLoop.join();
    _isLooping = true;
}

void GstPlayer::addBus()
{
    GstBus *bus = gst_pipeline_get_bus (GST_PIPELINE (_playElem));
    gst_bus_add_watch (bus, my_bus_callback, _loop);
    gst_object_unref (bus);
}

double GstPlayer::getVolume()
{
    double volume = 0;
    g_object_get (G_OBJECT (_playElem), "volume", &volume, NULL);
    return volume;
}

void GstPlayer::setVolume(double volume)
{
    volume=std::max(std::min(volume, 1.0), 0.0);
    g_object_set (G_OBJECT (_playElem), "volume", volume, NULL);
}

void GstPlayer::setMute(bool f)
{
    if(f)
        g_object_set (G_OBJECT (_playElem), "mute", TRUE, NULL);
    else
        g_object_set (G_OBJECT (_playElem), "mute", FALSE, NULL);
}

bool GstPlayer::getMute()
{
    gboolean mute=TRUE;
    g_object_get (G_OBJECT (_playElem), "mute", &mute, NULL);
    return mute == TRUE;
}
    

gboolean GstPlayer::my_bus_callback (GstBus *bus, GstMessage *msg, gpointer data)
{
    GMainLoop *loop = (GMainLoop *) data;

    switch (GST_MESSAGE_TYPE (msg)) {

    case GST_MESSAGE_EOS:
      g_print ("End of stream\n");
      g_main_loop_quit (loop);
      break;

    case GST_MESSAGE_ERROR: {
      gchar  *debug;
      GError *error;

      gst_message_parse_error (msg, &error, &debug);
      g_free (debug);

      g_printerr ("Error: %s\n", error->message);
      g_error_free (error);

      g_main_loop_quit (loop);
      break;
    }
    default:
      break;
    }

    return TRUE;
}

















