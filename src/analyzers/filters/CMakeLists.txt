project(meta-filters)

add_library(meta-filters alpha_filter.cpp
                         empty_sentence_filter.cpp
                         english_normalizer.cpp
                         filter_factory.cpp
                         icu_filter.cpp
                         length_filter.cpp
                         list_filter.cpp
                         lowercase_filter
                         porter2_stemmer.cpp
                         sentence_boundary.cpp)
target_link_libraries(meta-filters meta-utf porter2-stemmer)
