 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *   successfully closed or not, freopen opens the file specified by path
      /* Yes, open the file directly if no stream is opened yet */

      if (stream == NULL)
        {
          return fopen(path, mode);
        }

      /* Otherwise, open the file */

      oflags = lib_mode2oflags(mode);
      if (oflags < 0)
        {
          return NULL;
        }
      fd = open(path, oflags, 0666);
      if (fd < 0)
          return NULL;
      /* Flush the stream and duplicate the new fd to it */

      fflush(stream);
      ret = dup2(fd, fileno(stream));
      close(fd);
      if (ret < 0)
        {
          return NULL;
        }
      clearerr(stream);
      return stream;