idf_component_register(SRCS "parse_weather.c" "main.c" "toggle_led.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES
                        "../CERT/AMAZON.crt"
                        "../CERT/Amazon RSA 2048 M02.crt"
                    )
