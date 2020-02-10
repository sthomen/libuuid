#ifndef CONFIG_H
#define CONFIG_H

#ifdef __sgi
#define RAND_LENGTH 2
#else
#warning "Unknown platform, assuming 4 bytes of randomness from rand()"
#define RAND_LENGTH 4
#endif

#endif /* CONFIG_H */
