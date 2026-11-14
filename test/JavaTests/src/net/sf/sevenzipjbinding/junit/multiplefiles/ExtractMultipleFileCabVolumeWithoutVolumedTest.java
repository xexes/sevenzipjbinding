package net.sf.sevenzipjbinding.junit.multiplefiles;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;

import java.io.IOException;
import java.io.RandomAccessFile;

import org.junit.Test;

import net.sf.sevenzipjbinding.ArchiveFormat;
import net.sf.sevenzipjbinding.ExtractOperationResult;
import net.sf.sevenzipjbinding.IArchiveOpenCallback;
import net.sf.sevenzipjbinding.IArchiveOpenVolumeCallback;
import net.sf.sevenzipjbinding.IInArchive;
import net.sf.sevenzipjbinding.IInStream;
import net.sf.sevenzipjbinding.ISequentialOutStream;
import net.sf.sevenzipjbinding.PropID;
import net.sf.sevenzipjbinding.SevenZip;
import net.sf.sevenzipjbinding.SevenZipException;
import net.sf.sevenzipjbinding.impl.RandomAccessFileInStream;
import net.sf.sevenzipjbinding.junit.JUnitNativeTestBase;
import net.sf.sevenzipjbinding.junit.VoidContext;
import net.sf.sevenzipjbinding.simple.ISimpleInArchiveItem;

public class ExtractMultipleFileCabVolumeWithoutVolumedTest extends JUnitNativeTestBase<VoidContext> {

    /**
     * Callback implementation that provides both IArchiveOpenCallback and
     * IArchiveOpenVolumeCallback interfaces for multivolume CAB extraction.
     */
    private static class VolumeAwareCallback implements IArchiveOpenCallback, IArchiveOpenVolumeCallback {
        public Object getProperty(PropID propID) throws SevenZipException {
            return null;
        }

        public void setTotal(Long files, Long bytes) throws SevenZipException {
        }

        public void setCompleted(Long files, Long bytes) throws SevenZipException {
        }

        public IInStream getStream(String filename) throws SevenZipException {
            try {
                RandomAccessFile volFile = new RandomAccessFile(
                    "testdata/multiple-files/cab/" + filename, "r");
                return new RandomAccessFileInStream(volFile);
            } catch (IOException e) {
                throw new SevenZipException("Volume file not found: " + filename, e);
            }
        }
    }

    /**
     * Test providing IArchiveOpenVolumeCallback - should succeed. Autodetect format, with volume callback.
     * 
     * @throws Exception
     */
    @Test
    public void testWithAutodetectWithOpenVolumeCallback() throws Exception {
        test(true, true);
    }

    /**
     * Test providing IArchiveOpenVolumeCallback - should succeed. Explicit CAB format, with volume callback.
     * 
     * @throws Exception
     */
    @Test
    public void testWithoutAutodetectWithOpenVolumeCallback() throws Exception {
        test(false, true);
    }

    /**
     * Test WITHOUT IArchiveOpenVolumeCallback - should FAIL with SevenZipException. Autodetect format, no volume
     * callback.
     * 
     * @throws Exception
     */
    @Test(expected = SevenZipException.class)
    public void testWithAutodetect() throws Exception {
        test(true, false);
    }

    /**
     * Test WITHOUT IArchiveOpenVolumeCallback - should FAIL with SevenZipException. Explicit CAB format, no volume
     * callback.
     * 
     * @throws Exception
     */
    @Test(expected = SevenZipException.class)
    public void testWithoutAutodetect() throws Exception {
        test(false, false);
    }

    /**
     * Internal test method implementing the actual extraction logic.
     *
     * @param useAutodetect
     *            If true, use null for ArchiveFormat (autodetect). If false, use ArchiveFormat.CAB.
     * @param withOpenVolumeCallback
     *            If true, provide IArchiveOpenVolumeCallback implementation. If false, pass null - should cause
     *            SevenZipException when volumes needed.
     * @throws Exception
     */
    private void test(boolean useAutodetect, boolean withOpenVolumeCallback) throws Exception {
        RandomAccessFile randomAccessFile = null;
        IInArchive inArchive = null;
        boolean ok = false;

        try {
            randomAccessFile = new RandomAccessFile("testdata/multiple-files/cab/vol-archive1.zip.0.disk1.cab", "r");

            IArchiveOpenCallback archiveOpenCallback = null;
            if (withOpenVolumeCallback) {
                // Provide proper IArchiveOpenVolumeCallback implementation
                archiveOpenCallback = new VolumeAwareCallback();
            }

            inArchive = SevenZip.openInArchive(
                useAutodetect ? null : ArchiveFormat.CAB,
                new RandomAccessFileInStream(randomAccessFile),
                archiveOpenCallback);

            // Getting simple interface of the archive inArchive
            ISimpleInArchiveItem[] items = inArchive.getSimpleInterface().getArchiveItems();
            int extractedCount = 0;
            for (ISimpleInArchiveItem item : items) {
                if (!item.isFolder()) {
                    ExtractOperationResult result;
                    result = item.extractSlow(new ISequentialOutStream() {
                        public int write(byte[] data) throws SevenZipException {
                            return data.length; // Return amount of consumed data
                        }
                    });
                    assertTrue("Error extracting item: " + result, result == ExtractOperationResult.OK);
                    extractedCount++;
                }
            }
            // Verify we actually extracted something
            assertTrue("No files were extracted from the archive", extractedCount > 0);
            ok = true;
        } finally {
            if (inArchive != null) {
                try {
                    inArchive.close();
                } catch (SevenZipException e) {
                    if (ok) {
                        fail("Error closing archive: " + e);
                    }
                }
            }
            if (randomAccessFile != null) {
                try {
                    randomAccessFile.close();
                } catch (IOException e) {
                    if (ok) {
                        fail("Error closing file: " + e);
                    }
                }
            }
        }
    }
}
