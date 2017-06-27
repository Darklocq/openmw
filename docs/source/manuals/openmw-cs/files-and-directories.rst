Files and Directories
#####################

In this chapter of the manual we will cover the usage of files and directories
by OpenMW CS. Files and directories are file system concepts of your operating
system, so we will not be going into specifics about that, we will only focus
on what is relevant to OpenMW CS.


Basics
******


Directories
===========

OpenMW and OpenMW CS us multiple directories on the file system. First of all,
there is a *user directory* that holds configuration files and a number of
different sub-directories. The location of the user directory is hard-coded
into the CS and depends on your operating system.

.. To-do: Replace "<whatever>" below with correct information.

================  =========================================
Operating System  User Dircetory
================  =========================================
GNU/Linux         ``<whatever>``
OS X              ``~/Library/Application Support/openmw/``
Windows           ``<whatever>``
================  =========================================

In addition to this single hard-coded directory, both OpenMW and OpenMW CS
need a place to seek for the actual data files of the game: textures, meshes
(3D models), sounds, dialogue, record files that store objects in the game,
and so on. These files are called *content files*. We support multiple such
paths (we call them *data paths*) as specified in the configuration. Usually
one data path points to the original *Morrowind* game's ``Data Files`` directory,
unless you are creating an all-new game of your own.  You are free to specify
more data paths, however. There is one special data path that, as described later,
is used to store newly created content files.


Content files
=============

The original *Morrowind* engine by Bethesda Softworks uses two types of content
files: ``.esm`` (master) and ``.esp`` (plugin), and supports a third, ``.bsa``. The
distinction between these is not clear, and often confusing. One would expect
the ``ESM`` (master) file to be used to specify one master, which is then modified
by the ``ESP`` plugins. Indeed, this is the basic idea. However, the major official
expansions, *Tribunal* and *Bloodmoon*, were also made as ``ESM`` files, even though
they could essentially be described as really large plugins, and therefore should
rather use ``ESP`` files. There were technical reasons behind this decision – somewhat
valid in the case of the original engine. The third format, ``BSA``, is rarely used,
but can be thought of as an ``ESP`` alternative.

Clearly it is better to have a system that is more sensible and consistent.  OpenMW
achieves this by using our own content file types.

We support all of these file formats, but in order to make use of new features in
OpenMW one should consider using new file types designed with our engine in
mind: *game* files and *addon* files, collectively called *content files*.


OpenMW content files
--------------------

The concepts of *game* and *addon* files are somewhat similar to the old
concept of ``ESM`` and ``ESP``, but more strictly enforced. It is quite
straight-formward: If you want to make new game using OpenMW as the engine (a
so-called *total conversion*) you should create a game file. If you want to
create an addon for an existing game file, create an addon file. Nothing else
matters; the only distinction you should consider is if your project is about
creating a new game or changing an existing one. Simple as that.

Another simple thing about content files are the extensions: we are using
``.omwaddon`` for addon files and ``.omwgame`` for game files.


*Morrowind* content files
-----------------------

Using our content files is recommended for projects that are intended to used
with the OpenMW engine. However, some players might wish to still use the
original *Morrowind* engine. In addition, thousands of ``ESP`` (and, rarely,
``ESM``) have been created and released by the modder community since 2002,
some of them with really outstanding content. Because of this, OpenMW CS
simply has no choice but to support ``ESP/ESM`` files. If
you decidw to choose ``ESP/ESM`` files instead of using our own content file
types, you are most likely aimng at compatibility with the original engine. This
subject is covered in its own chapter of this manual.

The actual creation of new files is described in the next chapter. Here, we are
going to focus only on the details you need to know in order to create your
first OpenMW CS file. For now let's just remember that content files are created
inside the user directory in the ``data`` subdirectory (that is the one special
data directory mentioned earlier).


Dependencies
------------

Since an addon is supposed to change the game, it follows that it also depends
on the said game to work. We can conceptualise this with an example: your
modification is changing the price of an iron sword, but what if there is no
iron sword in game? That's right: we get nonsense. What you want to do is tie
your addon to the files you are changing. Those can be either game files (for
example when making an expansion island for a game) or other addon files
(making a house on said island). Obviously, it is a good idea to be dependent
only on files that are really changed in your addon, but sadly there is no
other way to achieve this than knowing what you want to do. Again, please
remember that this section of the manual does not cover creating the content
files – it is only a theoretical introduction to the subject. For now, just keep
in mind that dependencies exist, and is up to you to decide whether your
content file should depend on other content files.

Game files (as opposed to addon files) are not intended to have any dependencies
for a simple reason: the player is using only one game file at a time (excluding
the original *Morrowind* and its confusing ``ESP/ESM`` system); therefore no game file
can depend on another game file. Also, since a game file forms the base for addon
files it can not itself depend on addon files.


Project files
-------------

Project files act as containers for data not used by the OpenMW game engine
itself, but still useful for OpenMW CS. The primary example of this data
category is record filters (described in a later chapter of the manual). 
As a mod author, you probably do not need or want to distribute project
files at all; they are meant to be used only by you and your team.

.. TODO "you and your team": is that correct?

As you would imagine, project files make sense only in combination with actual
content files. In fact, each time you start to work on new content file and a
project file was not found, one will be created. The extension of project files
is ``.project``. The whole name of the project file is the whole name of the
content file, with that appended extension. For instance, a ``swords.omwaddon``
file is associated with a ``swords.omwaddon.project`` file.

Project files are stored inside the user directory, in the ``projects``
subdirectory. This is the path location for both freshly created project files,
and a place where OpenMW CS looks for already-existing files.


Resource files
==============

Unless we are talking about a fully text-based game, like *Zork* or *Rogue*, one
would expect that a video game is using some media files: 3D models with
textures, images acting as icons, sounds, and anything else. Since content
files, no matter whether they are *ESP*, *ESM* or new OpenMW file type, do not
contain any of those, it is clear that they have to be delivered with different
files – *resource files* of various sorts. These files have to be in formats
supported by the engine; otherwise they are just abstract data the game can't use.
Therefore this section will cover ways to add resource files with your content file,
and indicate what formats are supported. Later, you will learn how to make use of
those files in your content.


Audio
-----

OpenMW uses FFmpeg_ for audio playback, and so we support every audio type
supported by that library. This makes a huge list. Below is only a small portion
of the supported file types.

``.mp3`` (MPEG-1 Part 3 Layer 3)
   A popular audio file format and a de facto standard for storing audio. Used by
   the original *Morrowind* game.

``.ogg``
   An open-source multimedia container file using a high quality Vorbis_ audio
   codec. Recommended.


Video
-----

As in the case of audio files, we are using FFmepg to decode video files.
The list of supported files is long; we will cover only the most significant.

``.bik``
   Videos used by the original *Morrowind* game.

``.mp4``
   A multimedia container which use more advanced codecs (MPEG-4 Parts 2, 3 and
   10), with better audio and video compression rates, but also requiring more
   CPU-intensive decoding. This makes it probably less suited for storing
   sounds in computer games, but good for videos.

``.webm```
   A newer open-source video format with excellent compression. It also
   needs quite a lot of processing power to be decoded, but since game logic is
   not running during cutscenes, we can recommend it for use with OpenMW.

``.ogv``
   Alternative open-source container using the Theora_ codec for video and Vorbis
   for audio.


Textures and images
-------------------

The original Morrowind game uses ``.dds`` (DirectDraw Surface) and ``.tga`` (TARGA)
files for all kinds of two-dimensional images, and for textures to map onto 3D
meshes. In addition, the original engine supported ``.bmp`` files for some reason
(this is the Windows Bitmap format, which is terrible for a video game). We also
support an extended set of image files – including ``.jpg`` (JPEG), ``.png''
(Portable Network Graphic). These can be useful in some cases; for instance a JPEG
a valid option for a skybox texture, and PNG can useful for masks. However, please
keep in mind that JPEG images can grow to large sizes quickly and are not the best
option with a DirectX rendering backend. You probably still want to use ``.dds``
files for textures.


.. Hyperlink targets for the entire document

.. _FFmpeg: http://ffmpeg.org
.. _Vorbis: http://www.vorbis.com
.. _Theora: http://www.theora.org
