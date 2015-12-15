/** @file flink.h
 *  @brief Function prototypes and data structures for core module.
 *
 *  @author Martin Züger
 *  @author Urs Graf
 */
#ifndef FLINK_H_
#define FLINK_H_

//#include <linux/types.h>
//#include <linux/spinlock_types.h>
//#include <linux/list.h>
//#include <linux/fs.h>
#include <avr/io.h>

//typedef unsigned int ssize_t;	//TODO: Type?

// ############ flink error numbers ############
#define UNKOWN_ERROR -1

// FPGA module interface types
//extern const char* fmit_lkm_lut[];

// ############ Forward declarations ############
//struct flink_device;

// ############ flink private data ############
/** @brief Private data structure which is associated with a file.
 * The user library communicates with the kernel modules through read and write system calls
 * As a parameter a pointer to a file descriptor is passed. Within this structure the field @private_data
 * will hold the information about which device and subdevice will be targeted.
 */
// struct flink_private_data {
// 	struct flink_device*    fdev;
// 	struct flink_subdevice* current_subdevice;
// };

// ############ flink subdevice ############
#define MAX_NOF_SUBDEVICES 256
/// @brief Describes a subdevice
//struct flink_subdevice {
	//struct list_head     list;				/// Linked list of all subdevices of a device
// 	struct flink_device* parent;			/// Pointer to device which this subdevice belongs
// 	uint8_t              id;				/// Identifies a subdevice within a device
// 	uint16_t             function_id;		/// Identifies the function of the subdevice
// 	uint8_t              sub_function_id;	/// Identifies the subtype of the subdevice
// 	uint8_t              function_version;	/// Version of the function
// 	uint32_t             base_addr;			/// Base address (logical)
// 	uint32_t             mem_size;			/// Address space size
// 	uint32_t             nof_channels;		/// Number of channels
// 	uint32_t             unique_id;			/// unique id for this subdevice
// };


// ############ flink device ############
/// @brief Describes a device
struct flink_device {
	//struct list_head      list;			/// Linked list of all devices
	uint8_t               id;				/// Identifies a device
	uint8_t               nof_subdevices;	/// Number of subdevices
	//struct list_head      subdevices;		/// Linked list of all subdevices of this device
	struct flink_bus_ops* bus_ops;			/// Pointer to structure defining the bus operation functions of this device
	struct module*        appropriated_module;	/// Pointer to bus interface modul used for this device 
	void*                 bus_data;			/// Bus specific data
	//struct cdev*          char_device;		/// Pointer to cdev structure
	//struct device*        sysfs_device;		/// Pointer to sysfs device structure
};

// ############ Public functions ############
//extern struct flink_device*		flink_device_alloc(void);
extern void                    flink_device_init(struct flink_bus_ops* bus_ops);
extern void						flink_spi_init();

// extern int                     flink_device_add(struct flink_device* fdev);
// extern int                     flink_device_remove(struct flink_device* fdev);
// extern int                     flink_device_delete(struct flink_device* fdev);
// extern struct flink_device*    flink_get_device_by_id(uint8_t flink_device_id);
// extern struct flink_device*    flink_get_device_by_cdev(struct cdev* char_device);
// extern struct list_head*       flink_get_device_list(void);

// extern struct flink_subdevice* flink_subdevice_alloc(void);
// extern void                    flink_subdevice_init(struct flink_subdevice* fsubdev);
// extern int                     flink_subdevice_add(struct flink_device* fdev, struct flink_subdevice* fsubdev);
// extern int                     flink_subdevice_remove(struct flink_subdevice* fsubdev);
// extern int                     flink_subdevice_delete(struct flink_subdevice* fsubdev);
// extern struct flink_subdevice* flink_get_subdevice_by_id(struct flink_device* fdev, uint8_t flink_device_id);
// 
// extern struct class*           flink_get_sysfs_class(void);

//extern int                     flink_select_subdevice(struct file* f, uint8_t subdevice, uint8_t exclusive);

// ############ Constants ############
#define MAX_ADDRESS_SPACE 0x10000	/// Maximum address space for a flink device

// Memory addresses and offsets
#define MAIN_HEADER_SIZE		16	// byte
#define SUB_HEADER_SIZE			16	// byte
#define SUBDEV_FUNCTION_OFFSET	0x0000	// byte
#define SUBDEV_SIZE_OFFSET		0x0004	// byte
#define SUBDEV_NOFCHANNELS_OFFSET	0x0008	// byte
#define SUBDEV_UNIQUE_ID_OFFSET		0x000C	// byte
#define SUBDEV_STATUS_OFFSET		0x0010	// byte
#define SUBDEV_CONFIG_OFFSET		0x0014	// byte

// Types
#define INFO_FUNCTION_ID			0x00

// ############ I/O Controls ############

// IOCTL Commands
// #define SELECT_SUBDEVICE			0x10
// #define SELECT_SUBDEVICE_EXCL		0x11
// #define SELECT_SUBDEVICE 			0x10
// #define SELECT_SUBDEVICE_EXCL		0x11
// #define READ_NOF_SUBDEVICES			0x20
// #define READ_SUBDEVICE_INFO			0x21
// #define READ_SINGLE_BIT				0x30
// #define WRITE_SINGLE_BIT			0x31
// #define SELECT_AND_READ_BIT			0x40
// #define SELECT_AND_WRITE_BIT		0x41
// #define SELECT_AND_READ				0x42
// #define SELECT_AND_WRITE			0x43

// Userland types and sizes
/// @brief Structure containing information for ioctl system calls accessing single bits
// struct ioctl_bit_container_t {
// 	uint32_t offset;	
// 	uint8_t  bit;		
// 	uint8_t  value;		
// 	uint8_t  subdevice;
// };

// Userland types and sizes
/// @brief Structure containing information for ioctl system calls
// struct ioctl_container_t {
// 	uint8_t  subdevice;
// 	uint32_t offset;
// 	uint8_t  size;
// 	void*    data;
// };

// size of struct 'flink_subdevice' without linked list information (in bytes)
#define FLINKLIB_SUBDEVICE_SIZE		(sizeof(struct flink_subdevice)-offsetof(struct flink_subdevice,id))

#endif /* FLINK_H_ */
