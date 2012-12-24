/**
 * \file ResourceManager.h
 * \details Handles the loading and unloading of Allegro 5 resources.
 */

#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

class CResourceManager
{
public:

    ALLEGRO_BITMAP *loadBitmap( std::string filePath );
    ALLEGRO_SAMPLE *loadSample( std::string filePath );

private:

    shared_ptr <ALLEGRO_BITMAP> m_img;
    shared_ptr <ALLEGRO_SAMPLE> m_snd;
};

#endif // RESOURCE_MANAGER_H
