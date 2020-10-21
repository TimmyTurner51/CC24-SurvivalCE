#ifndef tileset_include_file
#define tileset_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define tileset_width 16
#define tileset_height 384
#define tileset_size 6146
#define tileset ((gfx_sprite_t*)tileset_data)
extern unsigned char tileset_data[6146];

#ifdef __cplusplus
}
#endif

#endif
