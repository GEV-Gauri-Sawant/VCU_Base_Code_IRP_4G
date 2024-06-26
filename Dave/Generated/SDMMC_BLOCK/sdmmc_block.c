
/**
 * @file sdmmc_block.c
 * @date 2016-08-24
 *
 * NOTE:
 * This file is generated by DAVE. Any manual modification done to this file will be lost when the code is regenerated.
 *
 * @cond
 ***********************************************************************************************************************
 * SDMMC_BLOCK v4.0.32 - The SDMMC_BLOCK APP is a generic SD/MMC card block device driver designed to drive SDMMC cards
 *                      with all relevant functionalities like writing or reading blocks of data from the card.
 *
 * Copyright (c) 2016-2020, Infineon Technologies AG
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,are permitted provided that the
 * following conditions are met:
 *
 *   Redistributions of source code must retain the above copyright notice, this list of conditions and the  following
 *   disclaimer.
 *
 *   Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
 *   following disclaimer in the documentation and/or other materials provided with the distribution.
 *
 *   Neither the name of the copyright holders nor the names of its contributors may be used to endorse or promote
 *   products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT  OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes
 * with Infineon Technologies AG (dave@infineon.com).
 ***********************************************************************************************************************
 *
 * Change History
 * --------------
 *
 * 2016-01-20:
 *     - Initial version. <br>
 *
 * 2016-02-05:
 *     - RTOS support added. <br>
 *     - Bug fixes done.<br>
 *
 * 2016-02-08:
 *     - Help Doc updated. <br>
 *     - Bug fixes done.<br>
 *
 * 2016-04-05:
 *     - Remove dead code <br>
 *     - MISRA fixes <br>
 *
 * @endcond
 */

/***********************************************************************************************************************
 * HEADER FILES
 **********************************************************************************************************************/

#include "sdmmc_block.h"

#ifdef SDMMC_BLOCK_SD
# if SDMMC_BLOCK_RTOS_MODE_SELECT
#  include "sdmmc_block_private_sd_rtos.h"
#else
#  include "sdmmc_block_private_sd.h"
# endif /* SDMMC_BLOCK_RTOS_MODE_SELECT */
#endif /* SDMMC_BLOCK_SD */

#ifdef SDMMC_BLOCK_SPI
# if SDMMC_BLOCK_RTOS_MODE_SELECT
#  include "sdmmc_block_private_spi_rtos.h"
#else
#  include "sdmmc_block_private_spi.h"
# endif /* SDMMC_BLOCK_RTOS_MODE_SELECT */
#endif /* SDMMC_BLOCK_SPI */

/***********************************************************************************************************************
 * MACROS
 **********************************************************************************************************************/

#define SDMMC_BLOCK_LOCK                 (0x4U) /* Lock the card */
#define SDMMC_BLOCK_UNLOCK               (0x0U) /* Unlock the card */
#define SDMMC_BLOCK_SET_PASSWD           (0x1U) /* Set the password for the card */
#define SDMMC_BLOCK_CLR_PASSWD           (0x2U) /* Clears the password */
#define SDMMC_BLOCK_SET_PASSWD_AND_LOCK  (0x5U) /* Set the password and locks the card */
#define SDMMC_BLOCK_FORCE_ERASE          (0x8U) /* Force erase the password data */

/***********************************************************************************************************************
 * LOCAL DATA
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * LOCAL ROUTINES
 **********************************************************************************************************************/

static SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_lFlushDiskWriteCache(SDMMC_BLOCK_t *obj);

/**********************************************************************************************************************
 * API IMPLEMENTATION
 **********************************************************************************************************************/

/* Retrieve the version of the SDMMC_BLOCK APP */
DAVE_APP_VERSION_t SDMMC_BLOCK_GetAppVersion(void)
{
  DAVE_APP_VERSION_t version;

  version.major = SDMMC_BLOCK_MAJOR_VERSION;
  version.minor = SDMMC_BLOCK_MINOR_VERSION;
  version.patch = SDMMC_BLOCK_PATCH_VERSION;

  return version;
}

/* SDMMC_BLOCK initialization function */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_Init(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_STATUS_t status = SDMMC_BLOCK_STATUS_SUCCESS;
  SDMMC_BLOCK_MODE_STATUS_t mode_status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;

  XMC_ASSERT("SDMMC_BLOCK_Init:Null obj is passed as input" , (obj != NULL));

  if (obj->init_flag == 1U)
  {
    status = SDMMC_BLOCK_STATUS_SUCCESS;
  }
  else
  {
    /* Setup pins */
    if (obj->init_pins != NULL)
    {
      obj->init_pins();
    }

#ifdef SDMMC_BLOCK_SPI
    if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
    {
      mode_status = SDMMC_BLOCK_SPI_Init(obj);
    }
#endif

#ifdef SDMMC_BLOCK_SD
    if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
    {
      mode_status = SDMMC_BLOCK_SD_Init(obj);
    }
#endif

    if (mode_status != SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      status = SDMMC_BLOCK_STATUS_FAILURE;
      obj->init_flag = 0U;
    }
    else
    {
      obj->init_flag = 1U;
    }
  }

  return status;
}

/* Initialize the card identification process */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_Initialize(SDMMC_BLOCK_t *const obj)
{
  SDMMC_BLOCK_MODE_STATUS_t mode_status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  SDMMC_BLOCK_STATUS_t status = SDMMC_BLOCK_STATUS_FAILURE;

  XMC_ASSERT("SDMMC_BLOCK_Initialize:Null obj is passed as input" , (obj != NULL));

#ifdef SDMMC_BLOCK_SPI
    if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
    {
      mode_status = SDMMC_BLOCK_SPI_CardIdentificationProcess(obj);
    }
#endif

#ifdef SDMMC_BLOCK_SD
    if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
    {
      mode_status = SDMMC_BLOCK_SD_CardIdentificationProcess(obj);
    }
#endif

    if (mode_status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      status = SDMMC_BLOCK_STATUS_SUCCESS;
    }

  return status;
}

/* Read the specified number of sectors of data from the specified address */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_ReadBlock(SDMMC_BLOCK_t *const obj,
                                           uint8_t* read_buf,
                                           const uint32_t sector_number,
                                           const uint8_t sector_count)
{
  SDMMC_BLOCK_STATUS_t status = SDMMC_BLOCK_STATUS_SUCCESS;

  XMC_ASSERT("SDMMC_BLOCK_ReadBlock:Null obj is passed as input" , (obj != NULL));
  XMC_ASSERT("SDMMC_BLOCK_ReadBlock:Read buffer address is invalid" , (read_buf != NULL));
  XMC_ASSERT("SDMMC_BLOCK_ReadBlock:Sector count to be read is zero" , (sector_count != 0U));

#ifdef SDMMC_BLOCK_SPI
  if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
  {
    status = SDMMC_BLOCK_SPI_ReadBlock(obj, read_buf, sector_number, (uint32_t)sector_count);
  }
#endif

#ifdef SDMMC_BLOCK_SD
  if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
  {
    status = SDMMC_BLOCK_SD_ReadBlock(obj, read_buf, sector_number, sector_count);
  }
#endif

  return status;
}

/* Write the specified number of sectors of data from the specified address */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_WriteBlock(SDMMC_BLOCK_t *const obj,
                                            uint8_t* write_buf,
                                            const uint32_t sector_number,
                                            const uint8_t sector_count)
{
  SDMMC_BLOCK_STATUS_t status = SDMMC_BLOCK_STATUS_SUCCESS;

  XMC_ASSERT("SDMMC_BLOCK_WriteBlock:Null obj is passed as input" , (obj != NULL));
  XMC_ASSERT("SDMMC_BLOCK_WriteBlock:Write buffer address is invalid" , (write_buf != NULL));
  XMC_ASSERT("SDMMC_BLOCK_WriteBlock:Sector count to be written is zero" , (sector_count != 0U));

#ifdef SDMMC_BLOCK_SPI
  if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
  {
    status = SDMMC_BLOCK_SPI_WriteBlock(obj, write_buf, sector_number, (uint32_t)sector_count);
  }
#endif

#ifdef SDMMC_BLOCK_SD
  if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
  {
    status = SDMMC_BLOCK_SD_WriteBlock(obj, write_buf, sector_number, sector_count);
  }
#endif

  return status;
}

/* Get the current status of the card */
uint8_t SDMMC_BLOCK_GetStatus(SDMMC_BLOCK_t *const obj)
{
  uint8_t disk_status = 0U;

#ifdef SDMMC_BLOCK_SPI
    if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
    {
      disk_status = SDMMC_BLOCK_SPI_GetState(obj);
    }
#endif

#ifdef SDMMC_BLOCK_SD
    if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
    {
      disk_status = SDMMC_BLOCK_SD_GetState(obj);
    }
#endif

  return disk_status;
}

/* I/O control */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_Ioctl(SDMMC_BLOCK_t *const obj, const uint8_t command, void *buffer)
{
  SDMMC_BLOCK_STATUS_t status = SDMMC_BLOCK_STATUS_SUCCESS;
  SDMMC_BLOCK_MODE_STATUS_t mode_status = SDMMC_BLOCK_MODE_STATUS_SUCCESS;
  uint8_t card_status;
  bool valid_command = true;
  SDMMC_BLOCK_ERASE_ADDRESS_t *erase_ptr;
  SDMMC_BLOCK_LOCK_STRUCTURE_t lock = {0U};
  const SDMMC_BLOCK_PASSWORD_t *password;

  XMC_ASSERT("SDMMC_BLOCK_WriteBlock:Null obj is passed as input" , (obj != NULL));

  /* If card is not initialized or inserted */
  if ((obj->card_state & (uint8_t)SDMMC_BLOCK_CARD_STATE_NOT_INITIALIZED) == (uint8_t)0)
  {
    card_status = SDMMC_BLOCK_GetStatus(obj);

    if ((card_status & (uint8_t)SDMMC_BLOCK_CARD_STATE_LOCKED) != 0U)
    {
      status = SDMMC_BLOCK_STATUS_LOCKED;
      if ((command == (uint8_t)SDMMC_BLOCK_CTRL_SYNC) ||
          (command == (uint8_t)SDMMC_BLOCK_MMC_GET_OCR) ||
          (command == (uint8_t)SDMMC_BLOCK_MMC_GET_SDSTAT) ||
          (command == (uint8_t)SDMMC_BLOCK_CTRL_TRIM))
      {
        valid_command = false;
      }
    }
  }
  else
  {
    valid_command = false;
    status = SDMMC_BLOCK_STATUS_NOTRDY;
  }

  if (valid_command == true)
  {
    /* Switch to the respective IOCTL command */
    switch (command)
    {
      /*
       * Control sync
       */
      case SDMMC_BLOCK_CTRL_SYNC:
        status = SDMMC_BLOCK_lFlushDiskWriteCache(obj);
        break;

      /*
       * Get sector size
       */
      case SDMMC_BLOCK_GET_SECTOR_SIZE:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetSectorSize(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetSectorSize(obj, buffer);
        }
#endif

      break;

      /*
       * Get sector count
       */
      case SDMMC_BLOCK_GET_SECTOR_COUNT:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetSectorCount(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetSectorCount(obj, buffer);
        }
#endif
        break;

      /*
       * Control trim. Erase the content in the specified sectors
       */
      case SDMMC_BLOCK_CTRL_TRIM:
        erase_ptr = (SDMMC_BLOCK_ERASE_ADDRESS_t *) buffer;
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_EraseBlock(obj, (erase_ptr->start_address), (erase_ptr->end_address));
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_EraseBlock(obj, (erase_ptr->start_address), (erase_ptr->end_address));
        }
#endif
        break;

      /*
       * Get block size
       */
      case SDMMC_BLOCK_GET_BLOCK_SIZE:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetBlockSize(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetBlockSize(obj, buffer);
        }
#endif
        break;

      /*
       * Get the type of the card
       */
      case SDMMC_BLOCK_MMC_GET_TYPE:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetCardType(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetCardType(obj, buffer);
        }
#endif
        break;

      /*
       * Get CSD
       */
      case SDMMC_BLOCK_MMC_GET_CSD:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetCsd(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetCsd(obj, buffer);
        }
#endif
        break;

      /*
       * Get CID
       */
      case SDMMC_BLOCK_MMC_GET_CID:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetCid(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetCid(obj, buffer);
        }
#endif
        break;

      /*
       * Get OCR
       */
      case SDMMC_BLOCK_MMC_GET_OCR:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetOcr(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetOcr(obj, buffer);
        }
#endif
        break;

      /*
       * Get SD status
       */
      case SDMMC_BLOCK_MMC_GET_SDSTAT:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_GetSdStatus(obj, buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetSdStatus(obj, buffer);
        }
#endif
        break;

      /*
       * Lock card
       */
      case SDMMC_BLOCK_MMC_LOCK_CARD:
        lock.mode = (uint8_t)SDMMC_BLOCK_LOCK;
        password = (const SDMMC_BLOCK_PASSWORD_t *)buffer;

        /* Check password length doesn't exceeds the permitted length */
        if (password->old_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH)
        {
          lock.pwd_len = password->old_pwd_len;
          memcpy(lock.pwd_data, password->old_pwd, lock.pwd_len);

#ifdef SDMMC_BLOCK_SPI
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
          {
            mode_status = SDMMC_BLOCK_SPI_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_LOCKED);
          }
#endif

#ifdef SDMMC_BLOCK_SD
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
          {
            mode_status = SDMMC_BLOCK_SD_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_LOCKED);
          }
#endif
        }
        else
        {
          mode_status = SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR;
        }
        break;

      /*
       * Unlock card
       */
      case SDMMC_BLOCK_MMC_UNLOCK_CARD:
        lock.mode = (uint8_t)SDMMC_BLOCK_UNLOCK;
        password = (const SDMMC_BLOCK_PASSWORD_t *)buffer;

        if (password->old_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH)
        {
          lock.pwd_len = password->old_pwd_len;
          memcpy(lock.pwd_data, password->old_pwd, lock.pwd_len);

#ifdef SDMMC_BLOCK_SPI
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
          {
            mode_status = SDMMC_BLOCK_SPI_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
          }
#endif

#ifdef SDMMC_BLOCK_SD
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
          {
            mode_status = SDMMC_BLOCK_SD_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
          }
#endif
        }
        else
        {
          mode_status = SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR;
        }
        break;

      /*
       * Set card password
       */
      case SDMMC_BLOCK_MMC_SET_PASSWD:
        lock.mode = (uint8_t)SDMMC_BLOCK_SET_PASSWD;
        password = (const SDMMC_BLOCK_PASSWORD_t *)buffer;

        if ((password->old_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH) &&
            (password->new_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH))
        {
          lock.pwd_len = password->old_pwd_len + password->new_pwd_len;
          memcpy(lock.pwd_data, password->old_pwd, password->old_pwd_len);
          memcpy(&lock.pwd_data[password->old_pwd_len], password->new_pwd, password->new_pwd_len);

    #ifdef SDMMC_BLOCK_SPI
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
          {
            mode_status = SDMMC_BLOCK_SPI_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
          }
    #endif

    #ifdef SDMMC_BLOCK_SD
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
          {
            mode_status = SDMMC_BLOCK_SD_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
          }
    #endif
        }
        else
        {
          mode_status = SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR;
        }
        break;

      /*
       * Clear card password
       */
      case SDMMC_BLOCK_MMC_CLEAR_PASSWD:
        lock.mode = (uint8_t)SDMMC_BLOCK_CLR_PASSWD;
        password = (const SDMMC_BLOCK_PASSWORD_t *)buffer;
        if (password->old_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH)
        {
          lock.pwd_len = password->old_pwd_len;
          memcpy(lock.pwd_data, password->old_pwd, lock.pwd_len);

#ifdef SDMMC_BLOCK_SPI
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
          {
            mode_status = SDMMC_BLOCK_SPI_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
          }
#endif

#ifdef SDMMC_BLOCK_SD
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
          {
            mode_status = SDMMC_BLOCK_SD_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
          }
#endif
        }
        else
        {
          mode_status = SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR;
        }
        break;

      /*
       * Set card lock
       */
      case SDMMC_BLOCK_MMC_SET_LOCK:
        lock.mode = (uint8_t)SDMMC_BLOCK_SET_PASSWD_AND_LOCK;
        password = (const SDMMC_BLOCK_PASSWORD_t *)buffer;

        if ((password->old_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH) &&
            (password->new_pwd_len <= (uint8_t)SDMMC_BLOCK_MAX_PASSWORD_LENGTH))
        {
          lock.pwd_len = password->old_pwd_len + password->new_pwd_len;
          memcpy(lock.pwd_data, password->old_pwd, password->old_pwd_len);
          memcpy(&lock.pwd_data[password->old_pwd_len], password->new_pwd, password->new_pwd_len);

#ifdef SDMMC_BLOCK_SPI
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
          {
            mode_status = SDMMC_BLOCK_SPI_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_LOCKED);
          }
#endif

#ifdef SDMMC_BLOCK_SD
          if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
          {
            mode_status = SDMMC_BLOCK_SD_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_LOCKED);
          }
#endif
        }
        else
        {
          mode_status = SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR;
        }
        break;

      /*
       * Read lock status
       */
      case SDMMC_BLOCK_MMC_READ_LOCK_STATUS:

#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status =  SDMMC_BLOCK_SPI_GetLockStatus(obj, (SDMMC_BLOCK_CARD_LOCK_STATUS_t *)buffer);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_GetLockStatus(obj, (SDMMC_BLOCK_CARD_LOCK_STATUS_t *)buffer);
        }
#endif
        break;

      /*
       * Force card erase
       */
      case SDMMC_BLOCK_MMC_FORCE_ERASE:
        lock.mode = (uint8_t)SDMMC_BLOCK_FORCE_ERASE;
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_LockUnlockCard(obj, &lock, SDMMC_BLOCK_CARD_LOCK_STATUS_UNLOCKED);
        }
#endif
        break;

      /*
       * Eject card
       */
      case SDMMC_BLOCK_CTRL_EJECT:
#ifdef SDMMC_BLOCK_SPI
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SPI)
        {
          mode_status = SDMMC_BLOCK_SPI_EjectCard(obj);
        }
#endif

#ifdef SDMMC_BLOCK_SD
        if (obj->interface_mode == SDMMC_BLOCK_CARD_INTERFACE_SD)
        {
          mode_status = SDMMC_BLOCK_SD_EjectCard(obj);
        }
#endif
        break;

      default:
        mode_status = SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR;
        break;
    }

    if (mode_status == SDMMC_BLOCK_MODE_STATUS_SUCCESS)
    {
      status = SDMMC_BLOCK_STATUS_SUCCESS;
    }
    else if (mode_status == SDMMC_BLOCK_MODE_STATUS_WP_VIOLATION_ERROR)
    {
      status = SDMMC_BLOCK_STATUS_WRPRT;
    }
    else if ((mode_status == SDMMC_BLOCK_MODE_STATUS_OUT_OF_RANGE_ERROR) ||
             (mode_status == SDMMC_BLOCK_MODE_STATUS_SECTOR_OUT_OF_BOUND))
    {
      status = SDMMC_BLOCK_STATUS_PARERR;
    }
    else
    {
      status = SDMMC_BLOCK_STATUS_FAILURE;
    }
  }

  return status;
}

#if SDMMC_BLOCK_SD_CARD_DETECTION_SUPPORT

#ifdef SDMMC_BLOCK_SD

/*
 * Registers the callback function for the card detection
 * mechanism.
 */
SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_RegisterCallback(SDMMC_BLOCK_t *const obj,
                                                  void (*cb)(SDMMC_BLOCK_SD_INTERRUPT_t))
{
  SDMMC_BLOCK_STATUS_t status = SDMMC_BLOCK_STATUS_PARERR;

  /* Check if the callback is not NULL */
  if (cb != NULL)
  {
    obj->sdmmc_sd->callback = cb;
    status = SDMMC_BLOCK_STATUS_SUCCESS;
  }

  return status;
}

#endif /* SDMMC_BLOCK_SD */

#endif /* SDMMC_BLOCK_SD_CARD_DETECTION_SUPPORT */

/***********************************************************************************************************************
 * LOCAL ROUTINES IMPLEMENTATION
 **********************************************************************************************************************/

/* Flush disk cache */
static SDMMC_BLOCK_STATUS_t SDMMC_BLOCK_lFlushDiskWriteCache(SDMMC_BLOCK_t *obj)
{
  /*
   * A flush is generally meant for writing filled buffers/cache to the
   * media. We're already ensuring that a write block(s) operation completes
   * before it exits WriteBlock().
   * So, this function does nothing at the moment. We are simply going to
   * return success
   */
  return SDMMC_BLOCK_STATUS_SUCCESS;
}
