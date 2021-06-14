/* code from https://stackoverflow.com/questions/44413446/why-is-range-v3-slower-than-the-stl-in-this-example
 */
#define NDEBUG

#include <numeric>
#include <vector>

#include <benchmark/benchmark.h>

#include <range/v3/all.hpp>

static void stl_search( benchmark::State &state ) {

	using namespace ranges;

	std::vector<long> lengths( state.range( 0 ), 1l );

	auto const to_find =
	  std::accumulate( lengths.begin( ), lengths.end( ), 0l ) / 2;

	while( state.KeepRunning( ) ) {

		auto accumulated_length = 0l;
		auto const found =
		  std::find_if( lengths.begin( ), lengths.end( ), [&]( auto const &val ) {
			  accumulated_length += val;
			  return to_find < accumulated_length;
		  } );
		volatile long val = std::distance( lengths.begin( ), found );
	}
	state.SetBytesProcessed( int64_t( state.iterations( ) ) *
	                         int64_t( state.range( 0 ) ) * sizeof( long ) );
}

static void ranges_search( benchmark::State &state ) {

	using namespace ranges;

	std::vector<long> lengths( state.range( 0 ), 1l );

	auto const to_find = accumulate( lengths, 0l ) / 2;

	while( state.KeepRunning( ) ) {
		volatile long val = distance(
		  lengths | view::partial_sum( ) |
		  view::take_while( [=]( auto const &i ) { return i <= to_find; } ) );
	}
	state.SetBytesProcessed( int64_t( state.iterations( ) ) *
	                         int64_t( state.range( 0 ) ) * sizeof( long ) );
}

BENCHMARK( ranges_search )->Range( 8 << 8, 8 << 16 );
BENCHMARK( stl_search )->Range( 8 << 8, 8 << 16 );

BENCHMARK_MAIN( );
