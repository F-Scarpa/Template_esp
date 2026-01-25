idf_component_register(SRCS "pushBtn.c" "main.c" "toggle_led.c"
                    INCLUDE_DIRS "."
                    EMBED_TXTFILES
                        "../CERT/AMAZON.crt"
                        "../CERT/Amazon RSA 2048 M02.crt"
                    )

fatfs_create_rawflash_image(storage ../site/dist FLASH_IN_PROJECT)