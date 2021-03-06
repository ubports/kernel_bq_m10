#include "yl_mmu_memory_functions.h"

#include "yl_mmu_mapper.h"
#include "yl_mmu_system_address_translator.h"

#include "yl_mmu_kernel_alloc.h"


YL_BOOL   
Remapper_memset( Mapper m, g3d_va_t ptr, unsigned char value, size_t size )
{
    pa_t pa;
    va_t va;
    RemapperIteratorRec iterRec;

    RemapperIterator_Init( & iterRec, m, ptr, size );

    while( RemapperIterator_valid( & iterRec ) )
    {
        pa      = RemapperIterator_get_pa( & iterRec );

        va      = pa_to_va( m, pa );

        yl_mmu_memset( (void *)va, value, size);
    }

    return 1;
}

YL_BOOL 
Remapper_memcpy( Mapper m, g3d_va_t destination, const g3d_va_t source, size_t size )
{
    pa_t paS, paD;
    va_t vaS, vaD;
    int lengthS, lengthD;
    RemapperIteratorRec iterRecSource;
    RemapperIteratorRec iterRecDest;

    RemapperIterator_Init( & iterRecSource, m, source, size );
    RemapperIterator_Init( & iterRecDest, m, destination, size );

    while( RemapperIterator_valid( & iterRecSource ) )
    {
        YL_MMU_ASSERT( RemapperIterator_valid( & iterRecDest ) );

        paS      = RemapperIterator_get_pa( & iterRecSource );
        lengthS  = RemapperIterator_next_4k( & iterRecSource );

        paD      = RemapperIterator_get_pa( & iterRecDest );
        lengthD  = RemapperIterator_next_4k( & iterRecDest );

        vaS      = pa_to_va( m, paS );
        vaD      = pa_to_va( m, paD );

        YL_MMU_ASSERT( lengthS == lengthD );

        yl_mmu_memcpy( (void *)vaD, (void *)vaS, lengthS);
    }

    return 1;
}


YL_BOOL 
Remapper_memcpy_from_g3d_va( Mapper m, va_t destination, const g3d_va_t source, size_t size )
{
    pa_t paS;
    va_t vaS, vaD;
    int lengthS;
    RemapperIteratorRec iterRecSource;

    RemapperIterator_Init( & iterRecSource, m, source, size );

    vaD = destination;
    while( RemapperIterator_valid( & iterRecSource ) )
    {
        paS      = RemapperIterator_get_pa( & iterRecSource );
        lengthS  = RemapperIterator_next( & iterRecSource );

        vaS      = pa_to_va( m, paS );

        yl_mmu_memcpy( (void *)vaD, (void *)vaS, lengthS);

        vaD      += lengthS;
    }

    return 1;
}

YL_BOOL 
Remapper_memcpy_to_g3d_va( Mapper m, g3d_va_t destination, const va_t source, size_t size )
{
    pa_t paD;
    va_t vaS, vaD;
    int lengthD;
    RemapperIteratorRec iterRecDest;

    RemapperIterator_Init( & iterRecDest, m, destination, size );

    vaS = source;
    while( RemapperIterator_valid( & iterRecDest ) )
    {
        paD      = RemapperIterator_get_pa( & iterRecDest );
        lengthD  = RemapperIterator_next( & iterRecDest );

        vaD      = pa_to_va( m, paD );

        yl_mmu_memcpy( (void *)vaD, (void *)vaS, lengthD);

        vaS      += lengthD;
    }

    return 1;
}


int 
Remapper_memcmp( Mapper m, va_t va, const g3d_va_t gva, size_t size )
{
    int ret;
    pa_t paS;
    va_t vaS;
    int lengthS;
    RemapperIteratorRec iter;

    RemapperIterator_Init( & iter, m, gva, size );

    while( RemapperIterator_valid( & iter ) )
    {
        paS      = RemapperIterator_get_pa( & iter );
        lengthS  = RemapperIterator_next( & iter );

        vaS      = pa_to_va( m, paS );

        ret = yl_mmu_memcmp( (const void *)va, (const void *)vaS, lengthS);

        if ( ret )
        {
            return ret;
        }

        va      += lengthS;
    }

    return 0;
}
